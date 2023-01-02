#include <algorithm>
#include <cmath>
#include <vector>

struct Point {
    int begining;
    int end;
    int weight;
};

struct Triangle {
  Point a, b, c;
};

// Compute the signed area of a triangle
double signed_area(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Check if a point is inside the circumcircle of a triangle
bool in_circumcircle(Point p, Triangle t) {
  double dx = p.x - t.a.x;
  double dy = p.y - t.a.y;
  double ex = t.b.x - t.a.x;
  double ey = t.b.y - t.a.y;
  double fx = t.c.x - t.a.x;
  double fy = t.c.y - t.a.y;

  double ap = dx * dx + dy * dy;
  double bp = ex * ex + ey * ey;
  double cp = fx * fx + fy * fy;

  return (dx * (ey * cp - bp * fy) -
          dy * (ex * cp - bp * fx) +
          ap * (ex * fy - ey * fx)) > 0;
}

// Compute the Delaunay triangulation of a set of points
std::vector<Triangle> delaunay_triangulation(std::vector<Point> points) {
  // Sort the points by increasing x coordinate
  std::sort(points.begin(), points.end(), [](Point a, Point b) {
    return a.x < b.x;
  });

  // Add a sentinel point at the end of the list
  Point sentinel = {INFINITY, INFINITY};
  points.push_back(sentinel);

  // Initialize the triangle list
  std::vector<Triangle> triangles;

  // Process the points one at a time
  for (int i = 0; i < points.size() - 1; i++) {
    // Find the triangle that contains the current point
    int j = triangles.size() - 1;
    while (j >= 0 && !in_circumcircle(points[i], triangles[j])) {
      j--;
    }

    // If no triangle was found, the point is on the convex hull
    if (j < 0) {
      // Add a new triangle with the point and the two sentinels
      Triangle t = {{points[i], points[i+1], sentinel}};
      triangles.push_back(t);
    } else {
      // Otherwise, delete the triangle and create new ones
      Triangle t = triangles[j];
      triangles.erase(triangles.begin() + j);
      triangles.push_back({t.a, t.b, points[i]});
      triangles.push_back({t.b, t.c, points[i]});

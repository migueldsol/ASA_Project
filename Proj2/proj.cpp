#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
using namespace std;

struct Edge{
    int begining;
    int end;
    int weight;
};

int getValue(){
    int lines;
    cin >> lines;
    return lines;
}

vector<int> getLineValues(int lines){
    vector<int> newVector;
    for (int counter = 0;counter < lines; counter++){
        int value;
        cin >> value;
        newVector.push_back(value);
    }
    return newVector;
}

// Compute the Delaunay triangulation of a set of edges
std::vector<Triangle> delaunay_triangulation(std::vector<Edge> edges) {
  // Sort the edges by increasing x coordinate of the beginning point
  std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
    return get_x(a.begin) < get_x(b.begin);
  });

  // Add a sentinel edge at the end of the list
  Edge sentinel = {-1, -1, INFINITY};
  edges.push_back(sentinel);

  // Initialize the triangle list
  std::vector<Triangle> triangles;

  // Process the edges one at a time
  for (int i = 0; i < edges.size() - 1; i++) {
    // Find the triangle that contains the current edge
    int j = triangles.size() - 1;
    while (j >= 0 && !in_circumcircle(edges[i], triangles[j])) {
      j--;
    }

    // If no triangle was found, the edge is on the convex hull
    if (j < 0) {
      // Add a new triangle with the edge and the two sentinels
      Triangle t = {{edges[i], edges[i+1], sentinel}};
      triangles.push_back(t);
    } else {
      // Otherwise, delete the triangle and create new ones
      Triangle t = triangles[j];
      triangles.erase(triangles.begin() + j);
      triangles.push_back({t.a, t.b, edges[i]});
      triangles.push_back({t.b, t.c, edges[i]});
      triangles.push_back({t.c, t.a, edges[i]});
    }
  }

  // Remove the sentinel triangles
  triangles.erase(std::remove_if(triangles.begin(), triangles.end(), [](Triangle t) {
    return t.a.weight == INFINITY || t.b.weight == INFINITY || t.c.weight == INFINITY;
  }), triangles.end());

  return triangles;
}

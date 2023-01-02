#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <stdio.h>

using namespace std;

// Vector of edges, where each edge is represented as a tuple
// containing the indices of the vertices that the edge connects,
// and the weight of the edge
vector<tuple<int, int, int>> edges;

vector<int> parent;

vector<int> vertex_rank;

// Initialize the minimum spanning tree
//vector<tuple<int, int, int>> mst;

int final_edges = 0;
int final_weight = 0;

// Find the set that a particular vertex belongs to
//TODO:Path compresion
int find_set(int vertex) {
  int num_parent = parent[vertex];
  if ( num_parent != vertex){
    return find_set(num_parent);
  }
  return num_parent;
}

int get_rank(int vertex){
  return vertex_rank[vertex];
}

int main() {
  // Read the number of nodes and edges
  int num_nodes;
  int num_edges;
  scanf("%d",&num_nodes);
  scanf("%d",&num_edges);

  // Read the edges and add them to the adjacency list
  for (int i = 0; i < num_edges; i++) {
    printf("entrei");
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    edges.push_back(tuple<int, int, int>{u, v, w});
    printf("sai");
  }
  printf("sai");

  // Sort the edges in ascending order by weight
    sort(edges.begin(), edges.end(), [](tuple<int, int, int>& a, tuple<int, int, int>& b) {
        return get<2>(b) < get<2>(a);
    });

    /* for (auto& e : edges) {
        int u = get<0>(e);
        int v = get<1>(e);
        int w = get<2>(e);
        cout << "(" << u << ", " << v << ", " << w << ")" << endl;
    } */

  // Initialize the vector of sets with a set for each vertex
  for (int i = 1; i <= num_nodes; i++){
    parent.push_back({i});
    vertex_rank.push_back({0});
    printf("parent[%d] = %d", i, parent[i]);
  }
  printf("sai");
  // Iterate through the sorted edges
  for (auto& e : edges) {
    int u = get<0>(e);
    int v = get<1>(e);
    int w = get<2>(e);
    // Find the sets that contain the vertices that the edge connects
    int set_u = find_set(u);
    int set_v = find_set(v);
    int rank_u = get_rank(u);
    int rank_v = get_rank(v);
    if(set_u != set_v){
      final_edges++;
      final_weight += w;
      if(rank_u > rank_v){
        parent[set_v] = set_u;
      }else{
        parent[set_u] = set_v;
        if(rank_u == rank_v){
          vertex_rank[set_v]++;
        }
      }
    }
    // Stop when all the vertices are in the same set, or when we have added all the edges to the minimum spanning tree
    if (final_edges == num_nodes - 1) {
      break;
    }
}
    cout << final_weight << endl;

  return 0;
}
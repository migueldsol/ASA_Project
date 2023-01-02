#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

// Vector of edges, where each edge is represented as a tuple
// containing the indices of the vertices that the edge connects,
// and the weight of the edge
vector<tuple<int, int, int>> edges;

vector<tuple<int,int>> parent_rank;

int final_edges = 0;
int final_weight = 0;

// Find the set that a particular vertex belongs to
int find_set(int vertex, int size) {
  for (int i = 1; i <= size; i++) {
    if (get<1>(parent_rank[vertex]) != vertex) {
      ;
    }
  }
  return -1;
}

int main() {
  // Read the number of nodes and edges
  int num_nodes;
  cin >> num_nodes;

  int num_edges;
  cin >> num_edges;

  // Read the edges and add them to the adjacency list
  for (int i = 0; i < num_edges; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.emplace_back(u, v, w);
  }

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
  for (int i = 1; i <= num_nodes; i++) {
    parent_rank.emplace_back(i,0);
  }

  // Initialize the minimum spanning tree
  vector<tuple<int, int, int>> mst;
  // Iterate through the sorted edges
  for (auto& e : edges) {
    int u = get<0>(e);
    int v = get<1>(e);
    int w = get<2>(e);
    // Find the sets that contain the vertices that the edge connects
    int set_u = find_set(u,num_nodes);
    int set_v = find_set(v,num_nodes);
    if(set_u == -1 || set_v == -1){
        break;
    }
    // If the sets are different, merge the sets and add the edge to the minimum spanning tree
    if (set_u != set_v) {
        mst.emplace_back(u, v, w);
        sets[set_u].insert(sets[set_v].begin(), sets[set_v].end());
        sets.erase(sets.begin() + set_v);
    }

    // Stop when all the vertices are in the same set, or when we have added all the edges to the minimum spanning tree
    if (sets.size() == 1 || mst.size() == num_nodes - 1) {
    break;
    }
}
    cout << mst.size() << endl;
    for (auto& e : mst) {
        int u = get<0>(e);
        int v = get<1>(e);
        int w = get<2>(e);
        cout << "(" << u << ", " << v << ", " << w << ")" << endl;
    }

  return 0;
}
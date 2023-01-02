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

// Vector of sets, where each set represents a disjoint subset of the vertices
vector<set<int>> sets;
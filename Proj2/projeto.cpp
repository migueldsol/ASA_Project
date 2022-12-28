#include <bits/stdc++.h>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define INF 1e9

//QUESTIONS pesos negativos?

//QUESTIONS linked list e a melhor representação?
unordered_map<int, unordered_map<int, int>> given_graph;
unordered_map<int, unordered_map<int, int>> graph;    


unordered_map<int, int> distances;
unordered_map<int, int> predecessor;



int counter = 0;

/*This function is an altered dijkstra. It gives the maximum value insted of the minimum*/
int dijkstra(int start, int end) {

    // Initialize-Single-Source
    for (auto& p : graph) {
        int vertex = p.first;
        distances[vertex] = -INF;
        predecessor[vertex] = 0;
    }

    // Set the distance from the start vertex to 0
    distances[start] = 0;

    /* Create "max queue" -> no need for max queue
     since we can just retrieve the max element of the set*/
    
    //QUESTIONS e preciso max queue? 
    
    set<int> unvisited;
    set<pair<int,int>> edgeVisited;

    for (auto& p : graph) {
        unvisited.insert(p.first);
    }

    // While univisited not empty relax adjacent vertexs
    while (!unvisited.empty()) {

        //Extract-Max
        int vertex = *max_element(unvisited.begin(), unvisited.end(), [](int a, int b) {
            return distances[a] < distances[b];
        });

        unvisited.erase(vertex);        //update unvisited

        // Find the vertex with the maximum distance
        for (auto& p : graph[vertex]){
            pair<int, int> pair1 = make_pair(vertex, p.first);
            pair<int, int> pair2 = make_pair(p.first, vertex);
            
            //avoiding edges we already calculated ->it might happen because its an undirected graph
            if ((edgeVisited.find(pair1) == edgeVisited.end() || edgeVisited.find(pair2) == edgeVisited.end())
             && distances[p.first] < distances[vertex] + p.second){
                distances[p.first] = distances[vertex] + p.second;
                predecessor[p.first] = vertex;
                
                edgeVisited.insert(pair1);
                edgeVisited.insert(pair2);
            }

        }
        
        // If we have reached the end vertex, break out of the loop
        if (vertex == end) {
            break;
        }
    }
    return distances[end];
}
/*This function applies the altered Dijkstra to all the vertices of the graph and returnes the maximum value*/
int apply_dijkstra_graph(){

    int max_dijkstra = -INF;
    set<pair<int,int>> visited;
    for (auto& p : graph){
        for (auto& q : graph){
            if (p.first != q.first){
                pair<int, int> pair1 = make_pair(p.first, q.first);
                pair<int, int> pair2 = make_pair(q.first, p.first);

                if (visited.find(pair1) == visited.end() || visited.find(pair2) == visited.end()){
                    int valueDijkstra = dijkstra(p.first, q.first);
                    printf("Djikstra between %d and %d is = %d\n", p.first, q.first, valueDijkstra);
                    if (valueDijkstra > max_dijkstra){
                        max_dijkstra = valueDijkstra;
                    }
                    visited.insert(pair1);
                    visited.insert(pair2);
                }
            }
        }
    }
    return max_dijkstra;
}
/*This function runs through the connected graph and adds it's edges to the unoredered_map graph*/
void dfs_separate(vector<bool> &visited, int vertex){
    for (auto& q : given_graph[vertex]){
        
        graph[vertex][q.first] = q.second;
        
        if (!visited[q.first]){
            visited[q.first] = true;

            dfs_separate(visited, q.first);
        }
    }
    return;
}

/*
this function turns a disconnected graph into multiple connected graphs and
sums the maximum value of applying dijkstra to those connected graphs 
*/
int separate_graphs(int v){
    vector<bool> visited(v, false);
    int sum_dijkstra = 0;
    for (auto& p : given_graph){
        if (!visited[p.first]){
            visited[p.first] = true;
            dfs_separate(visited, p.first);
            sum_dijkstra += apply_dijkstra_graph();
            graph.clear();
            distances.clear();
            predecessor.clear();
        }
    }
    return sum_dijkstra;
}



int main() {
    // Example graph
    int numberVertices;
    int numberEdges;
    //bool negativeWights;

    assert(scanf("%d", &numberVertices) != 0);
    assert(scanf("%d", &numberEdges) != 0);

    int vertice1, vertice2, weight;
    for (int i = 0; i < numberEdges; i++){
        assert(scanf("%d %d %d",&vertice1, &vertice2,&weight) != 0);
        given_graph[vertice1][vertice2] = weight;
        given_graph[vertice2][vertice1] = weight;
        
    }

    printf("%d\n",separate_graphs(numberVertices));
    return 0;
}
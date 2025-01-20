#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>

#include "Edge.h"
#include "UnionFind.h"

using namespace std;


// Union-Find structure with path compression and union by rank


// Function to parse input graph from a file
void parseGraph(const string& filename, int& n, vector<Edge>& edges) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    n = stoi(line); // Number of nodes

    // Skip node coordinates
    for (int i = 0; i < n; ++i) getline(file, line);

    getline(file, line); // Number of edges
    int e = stoi(line);

    for (int i = 0; i < e; ++i) {
        int u, v;
        double weight;
        file >> u >> v >> weight;
        edges.push_back({ u, v, weight });
    }
}

// Kruskal's algorithm to find the MST
pair<double, vector<Edge>> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end()); // Sort edges by weight
    UnionFind uf(n);
    vector<Edge> mst;
    double totalWeight = 0;

    for (const Edge& edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    return make_pair(totalWeight, mst);
}

int main() {
    int n; // Number of nodes
    vector<Edge> edges;

    // Parse graph from file
    parseGraph("D:\\minec\\Documents\\Projects\\Kruskal\\excercises\\g3.txt", n, edges);

    // Measure the performance
    auto start = chrono::high_resolution_clock::now();
    pair<double, vector<Edge>> result = kruskal(n, edges);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Output results
    cout << "Number of edges in MST: " << result.second.size() << endl;
    cout << "Total weight of MST: " << result.first << endl;
    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}

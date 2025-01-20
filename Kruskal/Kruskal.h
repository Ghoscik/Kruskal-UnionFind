#pragma once
#define KRUSKAL
#ifdef KRUSKAL

#include <iostream>
#include <algorithm>
#include <vector>

#include "Dlist.h"
#include "UnionFind.h"
#include "Edge.h"

#define gEdge pair<double, vector<Edge>>

using namespace std;

class Graph {
private:
    std::vector<Edge> graph;
    std::vector<Edge> MST;
    UnionFind uf;
    int nCount;

public:

    Graph(int nCount) : uf(nCount), nCount(nCount) {}

    void addEdge(const Edge& edge) 
    {
        graph.push_back(edge);
    }


    void makeMST() 
    {
        std::sort(graph.begin(), graph.end(), [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

        for (const auto& edge : graph) 
        {
            int uRep = uf.find(edge.u);
            int vRep = uf.find(edge.v);

            if (uRep != vRep) 
            {
                MST.push_back(edge);
                uf.unite(uRep, vRep);
            }
        }
    }

    void printMST() const {
        for (const auto& edge : MST) {
            std::cout << edge.u << " -- " << edge.v << " : " << edge.weight << "\n";
        }
    }
};


#endif
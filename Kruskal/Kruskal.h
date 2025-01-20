#pragma once
#define KRUSKAL
#ifdef KRUSKAL

#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>

#include "Dlist.h"
#include "UnionFind.h"
#include "Edge.h"

#define gEdge pair<double, Dlist<Edge>>

using namespace std;
using namespace std::chrono;

class Graph {
private:
    Dlist<Edge> graph;
    gEdge MST;
    UnionFind onion;
    uint64_t nCount, eCount;

public:

    Graph(uint64_t nCount) : onion(nCount), nCount(nCount), eCount(0) {}
    Graph(Dlist<Edge> graph, uint64_t nodes, uint64_t edges) : graph(graph), nCount(nodes), eCount(edges), onion(nodes) { }

    ~Graph() 
    {
        onion, graph = NULL;
        nCount, eCount = 0;
    }

    void addEdge(const Edge& edge) 
    {
        graph.push(edge);
    }

    uint64_t getFinds() { return onion.getFinds(); }

    void makeMST() 
    {
        cout << "For sorting: \t";
        auto start = high_resolution_clock::now();
        sort(graph.begin(), graph.end());
        handleTime(start);

        double totalWeight = 0;

        cout << "For main loop: ";
        start = high_resolution_clock::now();
        for (auto& edge : graph) 
        {
            int uRep = onion.find(edge.u);
            int vRep = onion.find(edge.v);

            if (uRep != vRep) 
            {
                MST.second.push(edge);
                onion.unite(uRep, vRep);
                totalWeight += edge.weight;
            }
        }
        handleTime(start);

        MST.first = totalWeight;

        cout << "Total find calls: \033[33m \t" << onion.getFinds() << "\033[0m" << endl;
        cout << "Total weight: \033[33m   \t" << MST.first << "\033[0m" << endl;

    }

    gEdge getMST() { return MST; }
    Dlist<Edge> getGraph() const { return graph; }

    uint64_t getEdges() { return eCount; }
    uint64_t getNodes() { return nCount; }

    //void printMST() const 
    //{
    //    for (auto& edge : MST.second) 
    //    {
    //        std::cout << edge.u << " -- " << edge.v << " : " << edge.weight << "\n";
    //    }
    //}

    void handleTime(steady_clock::time_point start)
    {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "\033[33m \tElapsed time: " << duration.count() << "us\033[0m" << endl;

    }
};


#endif
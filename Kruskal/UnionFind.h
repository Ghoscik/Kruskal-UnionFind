#pragma once
#define UNIONFIND
#ifdef UNIONFIND

#include "Dlist.h"
#include "Edge.h"

using namespace std;

class UnionFind {
private:
    Dlist<int> parent, rank;
    bool useCompr, useRank;
    uint64_t findCounter = 0;

public:
    UnionFind(int nCount) : parent(nCount), rank(nCount, 0), useCompr(true), useRank(true)
    {
        for (int i = 0; i < nCount; i++)
            parent[i] = i;
    }
    ~UnionFind()
    {
        findCounter = 0;
    }

    uint64_t getFinds() { return findCounter; }

    void settings(bool useCompression, bool useRanking)
    {
        this->useCompr = useCompression;
        this->useRank = useRanking;
    }

    int find(int node) 
    {
        findCounter++;
        if (parent[node] != node && useCompr)
            parent[node] = find(parent[node]);

        else if (parent[node] != node)
            parent[node] = node;
        
        return parent[node];
    }

    void unite(int nodeU, int nodeV) 
    {
        int rootU = find(nodeU);
        int rootV = find(nodeV);

        if (!useRank)
        {
            parent[rootU] = rootV;
            return;
        }

        if (rootU != rootV) 
        {
            if (rank[rootU] > rank[rootV]) 
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else 
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};


#endif
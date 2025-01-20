#pragma once
#define UNIONFIND
#ifdef UNIONFIND

#include <vector>
#include "Edge.h"

using namespace std;

class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int nCount) : parent(nCount), rank(nCount, 0)
    {
        for (int i = 0; i < nCount; i++)
            parent[i] = i;
    }

    int find(int node) 
    {
        if (parent[node] != node) 
            parent[node] = find(parent[node]);

        return parent[node];
    }

    void unite(int nodeU, int nodeV) 
    {
        int rootU = find(nodeU);
        int rootV = find(nodeV);

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
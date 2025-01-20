#pragma once
#define EDGE
#ifdef EDGE

struct Edge 
{
    int u, v;
    double weight;
    bool operator<(const Edge& other) const { return weight < other.weight; }
};

#endif // EDGE




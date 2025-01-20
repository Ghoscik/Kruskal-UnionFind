#include <iostream>
#include <chrono>

#include "Kruskal.h"
#include "hConsole.h"
#include "Dlist.h"

#define COLUMNS 4

using namespace std;
using namespace std::chrono;


void handleTime(steady_clock::time_point start);
void readFile(const string& filepath, Dlist<Edge>& graph, uint64_t& nodes, uint64_t& edges);
void makeTest(const string& filePath, bool useCompr, bool useRank);

int main() 
{
    const string files[3] = { "..\\excercises\\g1.txt", "..\\excercises\\g2.txt", "..\\excercises\\g3.txt" };

    
    for (auto& file : files)
    {
        cout << "\n================== " << file << " =======================\n" << endl;
        makeTest(file, 1, 1);
        makeTest(file, 0, 1);
        makeTest(file, 1, 0);
        makeTest(file, 0, 0);
    }

    return 0;
}

void makeTest(const string& filePath, bool useCompr, bool useRank)
{
    Dlist<Edge> graph;
    uint64_t nodes;
    uint64_t edges;

    cout << "\tpath compression = " << (bool)useCompr << "\n\t\t ranking = " << (bool)useRank << "\n\n";

    readFile(filePath, graph, nodes, edges);

    Graph kruskal(graph, nodes, edges);

    kruskal.makeMST();
    

    if (!useCompr && !useRank)
        return;

    cout << "--------------------------------------------" << endl;

}

void handleTime(steady_clock::time_point start)
{
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\033[33m \tElapsed time: " << duration.count() << "us\033[0m" << endl;

}


void readFile(const string& filepath, Dlist<Edge>& graph, uint64_t& nodes, uint64_t& edges)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filepath << endl;
        return;
    }

    string line;
    getline(file, line);
    nodes = stoi(line);

    for (uint64_t i = 0; i < nodes; ++i) getline(file, line);

    getline(file, line);
    edges = stoi(line);

    for (uint64_t i = 0; i < edges; ++i)
    {
        int u, v;
        double weight;
        file >> u >> v >> weight;
        graph.push({ u, v, weight });
    }
}


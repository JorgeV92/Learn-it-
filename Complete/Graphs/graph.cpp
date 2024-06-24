//////////////////////////////////////////////////////////////////////////////////////////////
//                                  Graphs 
//////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

class Graph {
public:
    Graph(int N, bool weighted, bool directed) : N(N), weighted(weighted), directed(directed) {
        if (weighted) {
            adj_weighted.resize(N);
        } else {
            adj.resize(N);
        }
    }

    void add_edge(int u, int v, int weight = 0) {
        if (weighted) {
            adj_weighted[u].push_back({v, weight});
            if (!directed) {
                adj_weighted[v].push_back({u, weight});
            }
        } else {
            adj[u].push_back(v);
            if (!directed) {
                adj[v].push_back(u);
            }
        }
    }

private:
    int N;
    bool weighted;
    bool directed;
    vector<vector<int>> adj;
    vector<vector<pair<int, int>>> adj_weighted;
};

int main() {
    Graph g1(5, false, false); // undirected, unweighted graph
    g1.add_edge(0, 1);
    g1.add_edge(1, 2);

    Graph g2(5, true, false); // undirected, weighted graph
    g2.add_edge(0, 1, 10);
    g2.add_edge(1, 2, 20);

    Graph g3(5, false, true); // directed, unweighted graph
    g3.add_edge(0, 1);
    g3.add_edge(1, 2);

    Graph g4(5, true, true); // directed, weighted graph
    g4.add_edge(0, 1, 10);
    g4.add_edge(1, 2, 20);

    return 0;
}
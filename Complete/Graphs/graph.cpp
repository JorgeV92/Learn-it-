//////////////////////////////////////////////////////////////////////////////////////////////
//                                  Graphs 
//////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <utility> 
#include <queue>
#include <functional>

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
    
    // refrerence for this at https://cp-algorithms.com/graph/breadth-first-search.html#__tabbed_1_1
    void bfs(int s, int t) {
        queue<int> q;
        vector<bool> used(N);           // vertices that are visited
        vector<int> d(N), p(N);         // distances and parents 

        q.push(s);
        used[s] = true;
        p[s] = -1;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : adj[v]) {
                if (!used[u]) {
                    used[u] = true;
                    q.push(u);
                    d[u] = d[v] + 1;
                    p[u] = v;
                }
            }
        }

        if (!used[t]) {
            cout << "No path!";
        } else {
            vector<int> path;
            for (int v = t; v != -1; v = p[v]) {
                path.push_back(v);
            } 
            reverse(path.begin(), path.end());
            cout << "Path: ";
            for (int v : path) cout << v << " ";
        }
        cout << endl;
    }

    void dfs(int s) {
        vector<bool> visited(N, false);
        vector<int> color(N, 0); // 0 = univisited, 1 = visited, 2 = existed

        vector<int> time_in(N, -1), time_out(N, -1);
        int dfs_timer = 0;

        function<void(int)> dfs_ = [&](int v) {
            time_in[v] = dfs_timer++;
            color[v] = 1;
            visited[v] = true;
            for (int u : adj[v]) {
                if (color[u] == 0) {
                    dfs_(u);
                }
            }
            color[v] = 2;
            time_out[v] = dfs_timer++;
        };
        dfs_(s);

        for (int i = 0; i < N; i++) {
            if (time_in[i] != -1) {     // Print only visited vertices
                cout << "Node " << i << ": Entry time = " << time_in[i] << ", Exit time = " << time_out[i] << endl; 
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

    g1.bfs(1, 2);
    g1.dfs(1);

    // Graph g2(5, true, false); // undirected, weighted graph
    // g2.add_edge(0, 1, 10);
    // g2.add_edge(1, 2, 20);

    // Graph g3(5, false, true); // directed, unweighted graph
    // g3.add_edge(0, 1);
    // g3.add_edge(1, 2);

    // Graph g4(5, true, true); // directed, weighted graph
    // g4.add_edge(0, 1, 10);
    // g4.add_edge(1, 2, 20);

    return 0;
}
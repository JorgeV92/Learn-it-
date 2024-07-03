////////////////////////////////////////////////////////////////////////
// 1976. Number of Ways to Arrive at Destination
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class ShortestPaths {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;

        // Adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& road : roads) {
            int u = road[0], v = road[1], time = road[2];
            graph[u].emplace_back(v, time);
            graph[v].emplace_back(u, time);
        }

        // Distance and ways arrays 
        vector<long long> dist(n, LLONG_MAX);
        vector<int> ways(n , 0);

        // Priority queue for Dijkstra's algorithm 
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

        dist[0] = 0;
        ways[0] = 1;
        pq.emplace(0, 0); // (distance, node)
        
        while (!pq.empty()) {
            auto[d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (const auto& [v, time] : graph[u]) {
                long long newDist = d + time;

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    ways[v] = ways[u];
                    pq.emplace(newDist, v);
                } else if (newDist == dist[v]) {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }
        return ways[n-1];
    }
};


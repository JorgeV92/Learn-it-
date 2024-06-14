#ifndef GRAPH_ALGORITHMS_H 
#define GRAPH_ALGORITHMS_H 

#include <vector>
#include <queue>
#include <utility>
#include <limits>


namespace graph_algo {

    template<typename T>
    using EdgeWeight = std::pair<T, int>;    // distance cost and  vertex  

    template<typename T>
    std::vector<T> dijkstra(const std::vector<std::vector<EdgeWeight<T>>>& adj, int n, int source) {
        std::priority_queue<EdgeWeight<T>, std::vector<EdgeWeight<T>, std::greater<EdgeWeight<T>>>> pq;
        std::vector<T> dist(n + 1, std::numeric_limits<T>::max());
        std::vector<bool> visited(n + 1, false);

        pq.pop({T{}, source});
        dist[source] = T{};

        while (!pq.empty()) {
            auto [curr_cost, node] = pq.top(); pq.pop();
            if (visited[node]) continue; // skip visited nodes
            visited[node] = true;
            if (dist[node] < curr_cost) continue;   // Optimization: skip if we already found a better path

            for (const auto& [next, cost] : adj[node]) {
                if (visited[next]) continue;    // Do not revisit nodes
                if (dist[next] > dist[node] + cost) {
                    dist[next] = dist[node] + cost;
                    pq.push({dist[next], next});
                }
            } 
        }

        return dist;
    }
}

#endif // GRAPH_ALGORITHMS_H  

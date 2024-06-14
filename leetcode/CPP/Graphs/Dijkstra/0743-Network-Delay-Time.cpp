/*
    0743. Network Delay Time    (Medium)

    You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel 
    times as direceted edges times[i] = (u_i, v_i, w_i) where u_i is the source node, v_i is the target 
    node, and w_i is the time it takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to 
    recieve the signal. If it is impossible for all the n nodes to recieve the signal, return -1.

    Example 1:

    Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    Output: 2
*/

#include <iostream>         // std::cout 
#include <vector>           // std::vector
#include <queue>            // std::priority_queue
#include <unordered_map>    // std::unordered_map
#include <algorithm>        // std::max_element
#include <limits>           // std::numeric_limits


class Dijkstra {
    public:
        int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
            // Adjacency list to represent the graph
            std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
            for (const auto& time : times) {
                int u = time[0]; // source node
                int v = time[1]; // target node
                int w = time[2]; // travel time
                graph[u].emplace_back(v, w);
            }

            // Priority queue to store {distance, node}
            // A min-heap to always expand the node with the smallest distance
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

            pq.emplace(0, k);

            // Vector to store the shortest distance to each node, with a initial large value
            std::vector<int> dist(n + 1, std::numeric_limits<int>::max());
            dist[k] = 0; // Distance to the starting node is 0

            // Dijkstra's algorithm
            while (!pq.empty()) {
                // Get the node with the smallest distance
                auto [currentDist, u] = pq.top(); pq.pop(); 
                // If the current distance is greater then the recorded shortest distance, skip it 
                // This condition prevents re-processing a node that has already been processed with 
                // a shorter distance 
                if (currentDist > dist[u]) continue;
                // Exploare all adjacent nodes (neighbors)
                for (const auto& [v, w] : graph[u]) {
                    // If a shorter path to v is found 
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w; // Update the shortest distance to v
                        pq.emplace(dist[v], v); // Push the updated distance and node into the queue
                    }
                }

            }
            // Find the maximum distance to all nodes
            int maxDist = *std::max_element(dist.begin() + 1, dist.end());

            // If the maximum distance is still the large value, return -1 (not all nodes are reachable)
            return maxDist == std::numeric_limits<int>::max() ? -1 : maxDist;
        }
};

int main (){
    Dijkstra dijkstra; 

    std::vector<std::vector<int>> times1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n1 = 4;
    int k1 = 2;
    std::cout << "Network delay time for example 1: " << dijkstra.networkDelayTime(times1, n1, k1) << std::endl;

    std::vector<std::vector<int>> times2 = {{1, 2, 1}};
    int n2 = 2;
    int k2 = 1;
    std::cout << "Network delay time for example 2: " << dijkstra.networkDelayTime(times2, n2, k2) << std::endl;


    std::vector<std::vector<int>> times3 = {{1, 2, 1}};
    int n3 = 2;
    int k3 = 2;
    std::cout << "Network delay time for example 3: " << dijkstra.networkDelayTime(times3, n3, k3) << std::endl;


    return 0;
}
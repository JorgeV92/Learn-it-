/*
    1514. Path with Maximum Probability     (Medium)

    You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list 
    where edge[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability 
    of success of travering edge succProb[i].

    Given two nodes start and end, find the path with the maximum probability of success to go 
    from start to end and return its success probability. 

    If there is no path from start to end, return 0. 

    Example 1:

    Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
    Output: 0.25000
    Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <limits>

class Dijkstra {
    public:
        double maxProbability(int n, std::vector<std::vector<int>>& edges, 
                                std::vector<double>& succProb, int start_node, int end_node) {
            // Adjacency list to represent the graph
            std::unordered_map<int, std::vector<std::pair<int, double>>> graph;
            for (size_t i = 0; i < edges.size(); i++) {
                int u = edges[i][0];
                int b = edges[i][1];
                double prob = succProb[i];
                // undirected graph
                graph[u].emplace_back(b ,prob);
                graph[b].emplace_back(u, prob);
            }
            // Priority queue to store (prob, node)
            // A max-heap to always expand the node with highest probability
            std::priority_queue<std::pair<double, int>> pq;
            pq.emplace(1.0, start_node);    // Initialize with starting node and prob 1 

            // Vector to store the maximum probability to reach node, initialized to 0
            std::vector<double> probabilities(n, 0.0);
            probabilities[start_node] = 1.0; // Probability to reach the starting node is 1

            // Dijkstra's algorithm
            while (!pq.empty()) {
                auto [currentProb, u] = pq.top(); pq.pop(); // Get the node with the highest probability 
                // If we reached the end_node, return the probability
                if (u == end_node) {
                    return currentProb;
                }

                // Explore all adjacent nodes (neighbors)
                for (const auto& [v, prob] : graph[u]) {
                    // If a higher probability path to v is found 
                    if (currentProb * prob > probabilities[v]) {
                        probabilities[v] = currentProb * prob;   // update the prob to reach v
                        pq.emplace(probabilities[v], v);    // push the updated prob and node into the queue
                    }
                }
            }
            // If the end_node is not reachable, return 0
            return 0.0;
        }
};

int main () {
    Dijkstra dijkstra;

    std::vector<std::vector<int>> edges1 = {{0, 1}, {1, 2}, {0, 2}};
    std::vector<double> succPro1 = {0.5, 0.5, 0.2};
    int n1 = 3;
    int start1 = 0;
    int end1 = 2;
    std::cout << "Maximum probability from " << start1 << " to " << end1 << ": "
              << dijkstra.maxProbability(n1, edges1, succPro1, start1, end1) << std::endl;

    return 0;
}
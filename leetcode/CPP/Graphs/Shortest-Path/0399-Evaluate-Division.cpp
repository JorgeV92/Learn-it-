/*
 _______ _     _  _____   ______ _______ _______ _______ _______       _____  _______ _______ _     _     
 |______ |_____| |     | |_____/    |    |______ |______    |         |_____] |_____|    |    |_____|     
 ______| |     | |_____| |    \_    |    |______ ______|    |         |       |     |    |    |     |     
                                                                                                       

    0399. Evaluate Division (Medium)

    You are given an array of variable pairs equations and an array of real numbers values, 
    where equations[i] = [A_i, B_i] and values[i] represent the equation A_i / B_i = values[i]. 
    Each A_i or B_i is a string that represents a single variable.

    You are also given some queries, where queries[j] = [C_j, D_j] represents the jth query where 
    you must find the answer for C_j / D_j = ?.

    Return the answers to all queries. If a single answer cannot be determined, return -1.0.

    No division of zero


    Example 1:

    Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
    Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
    Explanation: 
    Given: a / b = 2.0, b / c = 3.0
    queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
    return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
    note: x is undefined => -1.0
    Example 2:

    Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
    Output: [3.75000,0.40000,5.00000,0.20000]
    Example 3:

    Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
    Output: [0.50000,2.00000,-1.00000,-1.00000]
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Let use a graph-based implementation to represent each variable as a node and each division 
// equation as a directed edge with a weight representing the division result. To find the result of 
//each query, we can perform a search (BFS or DFS) on the graph.
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <utility>

class ShortestPath {
    public:
        std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations, 
                                        std::vector<double>& values, std::vector<std::vector<std::string>>& queries) {

            // Adjacency list to represent the graph
            std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> graph;
            for (size_t i = 0; i < equations.size(); i++) {
                std::string u = equations[i][0];
                std::string v = equations[i][1];
                double value = values[i];
                graph[u].emplace_back(v, value);
                graph[v].emplace_back(u, 1.0 / value);
            }

            // BFS 
            auto bfs = [&](const std::string& start, const std::string& end) -> double {
                if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
                    return -1.0; // If either variable is not in the graph
                }
                std::queue<std::pair<std::string, double>> q;
                std::unordered_map<std::string, bool> visisted;
                q.push({start, 1.0});
                visisted[start] = true;

                while (!q.empty()) {
                    auto [current, product] = q.front(); q.pop();
                    if (current == end) {
                        return product;
                    }
                    for (const auto& [neighbor, value] : graph[current]) {
                        if (!visisted[neighbor]) {
                            visisted[neighbor] = true;
                            q.push({neighbor, product * value});
                        }
                    }
                }
                return -1.0;  // If no path is found 
            };

            // Process each query 
            std::vector<double> results;
            for (const auto& query : queries) {
                results.push_back(bfs(query[0], query[1]));
            }
            return results;
        }
};


int main() {
    ShortestPath sp;

    std::vector<std::vector<std::string>> equations = {{"a", "b"}, {"b", "c"}};
    std::vector<double> values = {2.0 ,3.0};
    std::vector<std::vector<std::string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};

    std::vector<double> results = sp.calcEquation(equations, values, queries);
    for (double result : results) {
        std::cout << result << " ";
    }
    std::cout << std::endl;

    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. Graph representation:
//     - Method adjacency list to represent the graph. Each variable is a node, and each equation 
//       provides a directed edge with the given division result as the weight.
//     - For each equation A_i / B_i = values[i], we add two directed edges: A_i -> B_i with weight 
//       values[i] and B_i -> A_i with weight 1 / values[i].
// 2. BFS
//     - Lambda function for BFS 
//     - BFS starts from start and aims to find the shortest path to end.
//     - If either start or end is not in the graph, return -1.0
//     - Use a queue to explore nodes level-by-level, storing the current node and the 
//       cumulative product od the weights along the path.
//     - Mark nodes as visisted to avoid cycles.
//     - If we reach the end node, return the cumulative product.
//     - If the queue is exhausted without finding the end node, return -1.0
// 3. Processing Queries:
//     - For each query, call the bfs function with compute the result and store in the result.  
//////////////////////////////////////////////////////////////////////////////////////////////////////

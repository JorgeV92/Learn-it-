/*
 _______ _     _  _____   ______ _______ _______ _______ _______       _____  _______ _______ _     _     
 |______ |_____| |     | |_____/    |    |______ |______    |         |_____] |_____|    |    |_____|     
 ______| |     | |_____| |    \_    |    |______ ______|    |         |       |     |    |    |     |     
                                                                                                       

    2976. Minimum Cost to Convert String 1      (Medium)

    You are given two 0-indexed sourcce and target, both length n and consisting of 
    lowercase Englosh letters. You are also given two 0-indexed character arrays original and 
    changed, and an integer array cost, where cost[i] represents the cost of changing the character
    originial[i] to the character changed[i].

    You start with the string source. In one operation, you can pick a character x from the string and 
    change it to the character y at a cost of z if there exists any index j such that cost[j] == z,
    original[j] == x, and change[j] == y.

    Return the minimum cost to convert the string source to the string target using any number of 
    operations. If it is impossible to convert source to targer, return -1.


    Example 1:

    Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
    Output: 28
    Explanation: To convert the string "abcd" to string "acbe":
    - Change value at index 1 from 'b' to 'c' at a cost of 5.
    - Change value at index 2 from 'c' to 'e' at a cost of 1.
    - Change value at index 2 from 'e' to 'b' at a cost of 2.
    - Change value at index 3 from 'd' to 'e' at a cost of 20.
    The total cost incurred is 5 + 1 + 2 + 20 = 28.
    It can be shown that this is the minimum possible cost.

    Example 2:

    Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
    Output: 12
    Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, 
    ollowed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all 
    occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.


    Example 3:

    Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
    Output: -1
    Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
//      - Bellman-Ford algorithm 
//
//   Wkiki-Source -> https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
//
//  function BellmanFord(list vertices, list edges, vertex source) is 
//
//      // This implementation takes in a graph, represented as 
//      // lists of vertices (represented as integers [0..n-1]) and edges,
//      // and fills two arrays (distance and predecessor) holding 
//      // the shortest path from the source to each vertex
//     
//      distance := list of size n
//      predecessor := list of size n 
//
//      // Step 1: initialize the graph
//      for each vertex v in vertices do 
//          // Initalize the distance to all vertices to inifinity 
//          distance[v] := inf 
//          // And having a null predecessor 
//          predecessor[v] := null
//
//      // The distance from the source to itself is, of course, zero 
//      distance[source] := 0
//
//      // Step 2: relax edges repreatedly 
//      repeat |V| - 1 times:
//          for each edge (u, v) with weight w in edges do 
//              if distance[u] + w < distance[v] then 
//                  distance[v] := distance[u] + w
//                  predecessor[v] := u
//      // Step 3: check for negative-weight cycles 
//      for each edge (u, v) with weight w in edges do 
//          if distance[u] + w < distance[v] then 
//              predecessor[v] := u 
//              // A negative cycle exists; find a vertec on the cycel 
//              visited := list of size n initialized with false 
//              visited[v] := true 
//              while not visited[u] do 
//                  visited[u] := true
//                  u := predecessor[u]
//              // u is a vertec in a negative cycle, fint the cycle itself
//              ncycle := [u]
//              v := predecessor[u]
//              while v != u do 
//                  ncycle := concatenate([v], ncycle)
//                  v := predecessor[v]
//              error "Graph contains a negative-weight cycle", ncycle
//      return distance, predecessor
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
//      - Dijkstra's algorithm   
//
//   Wkiki-Source -> https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
//
//  function Dijkstra(Graph, source):
//      create vertex priority queue Q
//      dist[source] <- 0                   // Initialization 
//      Q.add_with_priority(source, 0)      // associate priority equals dist[.]
//
//      for each vertex v in Graph.Vertices:
//          if v ≠ source
//              prev[v] <- UNDEDINED       // Predecessor of v
//              dist[v] <- INFINIRT        // unknown distance from the source to v 
//              Q.add_with_priority(v, INFINITY)
//      while Q is not empty:              // The main loop
//          u <- Q.extract_min()           // Remove and return best vertex
//          for each neighbor v of u:      // Go through all v neighbors of u
//              alt <- dist[u] + Graph.Edges(u, v)
//              if alt < dist[v]:
//                  prev[v] <- u
//                  dist[v] <- alt
//                  Q.decrease_priority(v, alt)
//      return dist, prev          
///////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <functional>
#include <queue>

class ShortestPath {
    public:
        // NOT FULLY WORKING!!!!!!!!!!!
        long long minimumCostBellmanFord(std::string source, std::string target, std::vector<char>& original, 
                                std::vector<char>& changed, std::vector<int>& cost) {
            // Check for length 
            if (source.length() != target.length()) return -1;

            int n = source.length();
            int m = original.size();
            std::unordered_map<char, std::unordered_map<char, long long>> cost_map;

            // Initalize cost_map with a large value
            for (char c = 'a'; c <= 'z'; ++c) {
                for (char d = 'a'; d <= 'z'; ++d) {
                    cost_map[c][d] = (c == d) ? 0 : LLONG_MAX;
                }
            }

            // Fill in the initial costs
            for (int i = 0; i < m; i++) {
                cost_map[original[i]][changed[i]] = std::min(cost_map[original[i]][changed[i]], (long long)cost[i]);
            }

            // Bellman-Ford algorithm 
            for (int k = 0; k < 26; k++) {
                for (char c = 'a'; c <= 'z'; c++) {
                    for (char d = 'a'; d <= 'z'; d++) {
                        for (char e = 'a'; e <= 'z'; e++) {
                            if (cost_map[c][e] != LLONG_MAX && cost_map[e][d] != LLONG_MAX) {
                                cost_map[c][d] = std::min(cost_map[c][d], cost_map[c][e] + cost_map[e][d]);
                            }
                        }
                    }
                }
            }

            long long total_cost = 0;

            for (int i = 0; i < n; i++) {
                if (cost_map[source[i]][target[i]] == LLONG_MAX){
                    return -1;
                }
                total_cost += cost_map[source[i]][target[i]];
            }
            return total_cost;
        }
        // NOT EFFECIENT 
        long long minimumCostDijkstra(std::string source, std::string target, std::vector<char>& original, 
                                std::vector<char>& changed, std::vector<int>& cost) {
            // Set the graph using an unordered_map where each character points to a vector of {neighbor, cost} pairs
            std::unordered_map<char, std::vector<std::pair<char, int>>> graph;

            for (int i = 0; i < original.size(); i++) {
                graph[original[i]].emplace_back(changed[i], cost[i]);
            }

            // Distance array to store the minimum cost to transform from one character to another
            std::vector<std::vector<int>> min_cost(26, std::vector<int>(26, INT_MAX));

            // Dijkstra's algorithm 
            auto dijkstra = [&](char start) {
                std::vector<int> dist(26, INT_MAX);
                dist[start - 'a'] = 0;
                std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::greater<std::pair<int, char>>> pq;
                pq.push({0, start});

                while (!pq.empty()) {
                    auto [currenCost, currentNode] = pq.top(); pq.pop();
                    if (currenCost > dist[currentNode - 'a']) continue;

                    for (const auto& [neighbor, edgeCost] : graph[currentNode]) {
                        int newCost = currenCost + edgeCost;
                        if (newCost < dist[neighbor - 'a']) {
                            dist[neighbor - 'a'] = newCost;
                            pq.push({newCost, neighbor});
                        }
                    }
                }
                for (int i = 0; i < 26; ++i) {
                    min_cost[start - 'a'][i] = dist[i];
                }
            };
            // Run Dijkstra's algorithm for every character in the original transformation 
            for (char ch : original) {
                dijkstra(ch);
            }

            // Calculate the total cost to transform source to target 
            long long totalCost = 0;
            for (size_t i = 0; i < source.size(); i++) {
                if (source[i] == target[i]) continue;

                int cost = min_cost[source[i] - 'a'][target[i] - 'a'];
                if (cost == INT_MAX) return -1;
                totalCost += cost;
            }
            return totalCost;
        }
};

int main() {
    ShortestPath sp;
    
    std::vector<char> original1 = {'a', 'b', 'c', 'c', 'e', 'd'};
    std::vector<char> changed1 = {'b', 'c', 'b', 'e', 'b', 'e'};
    std::vector<int> cost1 = {2, 5, 5, 1, 2, 20};
    std::cout << "Minimum cost for example 1: " << sp.minimumCostDijkstra("abcd", "acbe", original1, changed1, cost1) << std::endl;
    // Output: 28

    std::vector<char> original2 = {'a', 'c'};
    std::vector<char> changed2 = {'c', 'b'};
    std::vector<int> cost2 = {1, 2};
    std::cout << "Minimum cost for example 2: " << sp.minimumCostDijkstra("aaaa", "bbbb", original2, changed2, cost2) << std::endl;
    // Output: 12

    std::vector<char> original3 = {'a'};
    std::vector<char> changed3 = {'e'};
    std::vector<int> cost3 = {10000};
    std::cout << "Minimum cost for example 3: " << sp.minimumCostDijkstra("abcd", "abce", original3, changed3, cost3) << std::endl;
    // Output: -1

    return 0;
}
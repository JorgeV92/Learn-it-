'''
    0743. Network Delay Time    (Medium)

    You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel 
    times as direceted edges times[i] = (u_i, v_i, w_i) where u_i is the source node, v_i is the target 
    node, and w_i is the time it takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to 
    recieve the signal. If it is impossible for all the n nodes to recieve the signal, return -1.

    Example 1:

    Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    Output: 2
'''

import heapq 
from collections import defaultdict
import sys 

class Dijkstra:
    def networkDelayTime(self, times: list[list[int]], n: int, k: int) -> int:
        # Adacency list to represent the graph
        graph = defaultdict(list)
        for  u, v, w in times:
            graph[u].append((v, w))
            
        # Priority queue to store (distance, node)
        # A min-heap to always expand the node with the smallest distance
        pq = [(0, k)]
        
        # Dictionary to store the shortest distance to each ndoe, with an initail large value
        dist = {i: float('inf') for i in range(1, n + 1)}
        dist[k] = 0 # Distance to the starting node is 0
        
        # Dijkstra's algorithm 
        while pq:
            currentDist, u = heapq.heappop(pq)
            # If the current distance is greater than the recorded shortest distance, skip it
            if currentDist > dist[u]:
                continue
            # Exploare all adjacent nodes (neighbors)
            for v, w in graph[u]:
                # If a shorter path to v is found 
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w               # Update the shortest distance to v
                    heapq.heappush(pq, (dist[v], v))    # Push the updated dustance and node into the queue
                    
        #  Find the maximum distance to all nodes
        maxDist = max(dist.values())
        
        # If the maximum distance is still the large value, return -1 (not all nodes are reachable)
        return maxDist if maxDist < float('inf') else -1
    
    
if __name__ == "__main__":
    dijkstra = Dijkstra()
    
    times1 = [[2, 1, 1], [2, 3, 1], [3, 4, 1]]
    n1 = 4
    k1 = 2
    print(f"Network delay time for example 1: {dijkstra.networkDelayTime(times1, n1, k1)}")
    
    times2 = [[1, 2, 1]]
    n2 = 2
    k2 = 1
    print(f"Network delay time for example 2: {dijkstra.networkDelayTime(times2, n2, k2)}")
    
    times3 = [[1, 2, 1]]
    n3 = 2
    k3 = 2
    print(f"Network delay time for example 3: {dijkstra.networkDelayTime(times3, n3, k3)}")


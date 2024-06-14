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
#include <queue>           
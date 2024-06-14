(* 
  0743. Network Delay Time    (Medium)

    You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel 
    times as direceted edges times[i] = (u_i, v_i, w_i) where u_i is the source node, v_i is the target 
    node, and w_i is the time it takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to 
    recieve the signal. If it is impossible for all the n nodes to recieve the signal, return -1.

    Example 1:

    Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    Output: 2   
*)

open Printf
open Hashtbl

module IntPair = struct 
  type t = int * int 
  let compare (a1, b1) (a2, b2) = compare a1 a2
end

module PQ = Set.Make(IntPair)

let network_delay_time times n k = 
  (* Create adjacency list to represent the graph *)
  let graph = Hashtbl.create n in 
  List.iter (fun (u, v, w) -> 
    let neighbors = try Hashtbl.find graph u with Not_found -> [] in 
    Hashtbl.replace graph u ((v, w) :: neighbors)
    ) times;

  (* Priority queue to store (distance, node) *)
  let pq = ref PQ.empty in 
  pq := PQ.add (0, k) !pq;

  (* Array to store the shortest distance to each node, with an inital large value *)
  let dist = Array.make (n + 1) max_int in
  dist.(k) <- 0;

  (* Dijkstra's algorithm *)
  while not (PQ.is_empty !pq) do 
    let (currentDist, u) = PQ.min_elt !pq in 
    pq := PQ.remove (currentDist, u) !pq;
    if currentDist <= dist.(u) then 
      match Hashtbl.find_opt graph u with 
        | Some neighbors -> 
          List.iter (fun (v, w) -> 
            if dist.(v) > dist.(u) + w then begin 
              dist.(v) <- dist.(u) + w;
              pq := PQ.add (dist.(v), v) !pq
            end
            ) neighbors
        | None -> ()
    done;

    (* Find the maximum distance to all nodes *)
    let maxDist = Array.fold_left max (-1) (Array.sub dist 1 n) in 

    (* If the maximum distance is still the large value, return -1 (not all nodes are reachable) *)
    if maxDist = max_int then -1 else maxDist

let () = 
    let times1 = [(2, 1, 1); (2, 3, 1); (3, 4, 1)] in 
    let n1 = 4 in
    let k1 = 2 in 
    printf "Network delay time for example 1: %d\n" (network_delay_time times1 n1 k1);

    let times2 = [(1, 2, 1)] in
    let n2 = 2 in
    let k2 = 1 in
    printf "Network delay time for example 2: %d\n" (network_delay_time times2 n2 k2);

    let times3 = [(1, 2, 1)] in
    let n3 = 2 in
    let k3 = 2 in
    printf "Network delay time for example 3: %d\n" (network_delay_time times3 n3 k3)
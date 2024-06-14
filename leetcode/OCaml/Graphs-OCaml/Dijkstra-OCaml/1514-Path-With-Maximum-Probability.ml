(* 
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
*)

open Printf
open Hashtbl

module FloatPair = struct 
  type t = float * int 
  let compare (a1, b1) (a2, b2) = compare a2 a1 (* Reverse order for max-heap behavior *)
end

module PQ = Set.Make(FloatPair)

exception Found of float 

let max_probability n edges succPro start_node end_node = 
  (* Adjacency list to represent the graph *)
  let graph = Hashtbl.create n in 
  List.iteri (fun i (u, v) -> 
    let prob = succPro.(i) in 
    let neighbors_u = try Hashtbl.find graph u with Not_found -> [] in 
    let neighbors_v = try Hashtbl.find graph v with Not_found -> [] in 
    Hashtbl.replace graph u ((v, prob) :: neighbors_u); 
    Hashtbl.replace graph v ((u, prob) :: neighbors_v)
    ) edges;

  (* Priority queue to store (probability, node) *)
  let pq = ref PQ.empty in 
  pq := PQ.add (1.0, start_node) !pq;

  (* Array to store the maximum probability to reach each node, initialized to 0 *)
  let probabilities = Array.make n 0.0 in 
  probabilities.(start_node) <- 1.0;

  (* Dijkstra's algorithm *)
  while not (PQ.is_empty !pq) do 
    let (currentProb, u) = PQ.min_elt !pq in 
    pq := PQ.remove (currentProb, u) !pq; 
    if u = end_node then 
      (* if we reached the end_node, return probability *)
      raise (Found currentProb)
    else
      match Hashtbl.find_opt graph u with 
        | Some neighbors -> 
          List.iter (fun (v, prob) -> 
            if currentProb *. prob > probabilities.(v) then begin
              probabilities.(v) <- currentProb *. prob;
              pq := PQ.add (probabilities.(v), v) !pq
            end
          ) neighbors 
        | None -> ()
    done;
    (* If the end_node is not reachable, return 0 *)
    0.0

let () =
  let edges1 = [ (0, 1); (1, 2); (0, 2) ] in
  let succProb1 = [| 0.5; 0.5; 0.2 |] in
  let n1 = 3 in
  let start1 = 0 in
  let end1 = 2 in
  let result1 = max_probability n1 edges1 succProb1 start1 end1 in
  printf "Maximum probability from %d to %d: %f\n" start1 end1 result1
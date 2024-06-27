(* 
  I try to use and learn how to represent graphs in ocaml using https://ocaml.org/exercises#80
*)

(* Definition of graph as a pair of two sets (nodes and edges) *)
type 'a graph_term = {nodes : 'a list; edges : ('a * 'a) list}

(* Example of a graph *)

let example_graph = 
  {nodes = ['b'; 'c'; 'd'; 'g'; 'h'; 'k']; 
    edges = [('h', 'g'); ('k', 'f'); ('f', 'b'); ('f', 'c'); ('c', 'b')]}


(* Adjacency-list form *)
module CharMap = Map.Make(Char)

type 'a adjacency_list = 'a list CharMap.t

(* Function to convert a graph in graph_term form to adjacency_list formm *)
let to_adjacency_list graph = 
  let add_edge map (src, dst) =
    let adj = match CharMap.find_opt src map with 
      | Some l -> dst :: l 
      | None -> [dst]
    in
    CharMap.add src adj map
  in 
  List.fold_left add_edge CharMap.empty graph.edges
  
let example_adj_list = to_adjacency_list example_graph

(* print adjacency list *)
let print_adjacency_list adj_list = 
  CharMap.iter (fun key value -> 
    Printf.printf "%c: " key; 
    List.iter (fun v -> Printf.printf "%c " v) value;
    print_newline ()
    ) adj_list

(* let () = print_adjacency_list example_adj_list *)

(* Human-friendly form *)
(* "b-c f-c g-h d f-b k-f h-g";; *)

let compare_edges (a1, b1) (a2, b2) = 
  let cmp = compare a1 a2 in 
  if cmp = 0 then compare b1 b2 else cmp

let graph_human_friendly graph = 
  let edge_to_string (a, b) = Printf.sprintf "%c-%c" a b in 
  let sorted_edges = List.sort compare_edges graph.edges in 
  let edges_strings = List.map edge_to_string sorted_edges in 
  String.concat " " edges_strings

let example_human_friendly = graph_human_friendly example_graph

(* let () = Printf.printf "%s\n" example_human_friendly *)

(* 
   Path From One Node to Another One 

   Write a function pahts g a b that returns all acyclic path from node a to node b <> a in the graph g. The function should 
   return the list of all paths via backtracking.

*)

let neighbors g a cond = 
  let edge l (b, c) = if b = a && cond c then c :: l
                      else if c = a && cond b then b :: l
                      else l in 
  List.fold_left edge [] g.edges 

let rec list_path g a to_b = match to_b with 
  | [] -> assert false (* [to_b] contains the path to [b] *)
  | a' :: _ -> 
    if a' = a then [to_b]
    else 
      let n = neighbors g a' (fun c -> not (List.mem c to_b)) in 
      List.concat_map (fun c -> list_path g a (c :: to_b)) n 

let paths g a b = 
  assert (a <> b);
  list_path g a [b]

(* let example_paths = paths example_graph 'c' 'b' *)

let print_paths paths = 
  List.iter (fun path -> 
    List.iter (fun node -> Printf.printf "%c " node) path;
    print_newline ()
    ) paths 

(* let () = print_paths example_paths *)



(* 
    Cycle From a Given Node 
    
    Write a functions cycle g a that returns a closed path (cycle) p starting at a given node a in the graph g. 
    The predicate should return the list of all cycles via backtracking.

*)


let cycles g a = 
  Printf.printf "Looking for cycles...\n";
  let module CharSet = Set.Make(struct type t = char list let compare = compare end) in
  let n = neighbors g a (fun _ -> true) in 
  let p = List.concat_map (fun c -> list_path g a [c]) n in 
  let cycle_set = List.fold_left (fun set path -> CharSet.add (path @ [a]) set) CharSet.empty p in 
  CharSet.elements cycle_set

let example_cycles = cycles example_graph 'b' 

let () = print_paths example_cycles


(* Construct All Spanning Trees *)
(* 
   Write a function s_tree g to construct (by backtracking) all spanning trees of a given graph g.
   With this predicate, find out how many spanning trees there are for the graph depicted to the left. 
   The data of this example graph can be found in the test below. When you have a correct solution for 
   the s_tree function, use it to define two other useful functions: is_tree graph and is_connected Graph. 
   Both are five-minutes tasks! 
*)
let g = {nodes = ['a'; 'b'; 'c'; 'd'; 'e'; 'f'; 'g'; 'h'];
         edges = [('a', 'b'); ('a', 'd'); ('b', 'c'); ('b', 'e');
                  ('c', 'e'); ('d', 'e'); ('d', 'f'); ('d', 'g');
                  ('e', 'h'); ('f', 'g'); ('g', 'h')]}

let is_connected graph = 
  let rec dfs visited node = 
    if List.mem node visited then visited
    else
      let neighbors = List.fold_left (fun acc (a, b) ->
        if a = node && not (List.mem b visited) then b :: acc
        else if b = node && not (List.mem a visited) then a :: acc
        else acc
      ) [] graph.edges in 
      List.fold_left dfs (node :: visited) neighbors
  in 
  let visited_nodes = dfs [] (List.hd graph.nodes) in 
  List.length visited_nodes = List.length graph.nodes
  

let is_acyclic graph =
  let rec has_cycle visited stack node = 
    if List.mem node stack then true
    else 
      let neighbors = List.fold_left (fun acc (a, b) -> 
        if a = node && not (List.mem b visited) then b :: acc 
        else if b = node && not (List.mem a visited) then a :: acc 
        else acc
      ) [] graph.edges in 
      List.exists (has_cycle (node :: visited) (node :: stack)) neighbors
  in
  not (has_cycle [] [] (List.hd graph.nodes))


let is_tree graph = 
  is_connected graph && is_acyclic graph
  
(* Generate all subsets of a list *)
let rec subsets lst = 
  match lst with 
    | [] -> [[]]
    | x :: xs -> 
      let rest = subsets xs in 
      rest @ List.map (fun subset -> x :: subset) rest 

(* All spanning trees *)
let s_tree graph = 
  let edges = graph.edges in 
  let all_subsets = subsets edges in 
  let spanning_trees = List.filter (fun subset -> 
    let subgraph = {nodes = graph.nodes; edges = subset} in 
    is_tree subgraph && List.length subset = List.length graph.nodes - 1
  ) all_subsets in
  List.map (fun edges -> {nodes = graph.nodes; edges}) spanning_trees


let all_spanning_trees = s_tree g 

let print_graph graph = 
  Printf.printf "\n All Spanning trees\n";
  List.iter (fun (a, b) -> Printf.printf "(%c, %c) " a b) graph.edges;
  print_newline ()

(* let () = List.iter print_graph all_spanning_trees *)

(* ******************************************************************************************** *)

                (* Construct the Minimal Spanning Tree Kruskal's algorithm *)

(* Definition of graph as a pair of two sets (nodes and edges) *)
type 'a graph_term = {nodes : 'a list; edges : ('a * 'a) list}

(* Example graph *)
let g = {nodes = ['a'; 'b'; 'c'; 'd'; 'e'; 'f'; 'g'; 'h'];
         edges = [('a', 'b'); ('a', 'd'); ('b', 'c'); ('b', 'e');
                  ('c', 'e'); ('d', 'e'); ('d', 'f'); ('d', 'g');
                  ('e', 'h'); ('f', 'g'); ('g', 'h')]}

(* Check if the graph is connected *)
let is_connected graph = 
  let rec dfs visited node = 
    if List.mem node visited then visited
    else
      let neighbors = List.fold_left (fun acc (a, b) ->
        if a = node && not (List.mem b visited) then b :: acc
        else if b = node && not (List.mem a visited) then a :: acc
        else acc
      ) [] graph.edges in 
      List.fold_left dfs (node :: visited) neighbors
  in 
  let visited_nodes = dfs [] (List.hd graph.nodes) in 
  List.length visited_nodes = List.length graph.nodes

(* Check if the graph is acyclic *)
let is_acyclic graph =
  let rec has_cycle visited stack node = 
    if List.mem node stack then true
    else 
      let neighbors = List.fold_left (fun acc (a, b) -> 
        if a = node && not (List.mem b visited) then b :: acc 
        else if b = node && not (List.mem a visited) then a :: acc 
        else acc
      ) [] graph.edges in 
      List.exists (has_cycle (node :: visited) (node :: stack)) neighbors
  in
  not (has_cycle [] [] (List.hd graph.nodes))

(* Check if the graph is a tree *)
let is_tree graph = 
  is_connected graph && is_acyclic graph

(* Generate all subsets of a list *)
let rec subsets lst = 
  match lst with 
    | [] -> [[]]
    | x :: xs -> 
      let rest = subsets xs in 
      rest @ List.map (fun subset -> x :: subset) rest 

(* All spanning trees *)
let s_tree graph = 
  let edges = graph.edges in 
  let all_subsets = subsets edges in 
  let spanning_trees = List.filter (fun subset -> 
    let subgraph = {nodes = graph.nodes; edges = subset} in 
    is_tree subgraph && List.length subset = List.length graph.nodes - 1
  ) all_subsets in
  List.map (fun edges -> {nodes = graph.nodes; edges}) spanning_trees

let all_spanning_trees = s_tree g 

let print_graph graph = 
  Printf.printf "\nSpanning tree:\n";
  List.iter (fun (a, b) -> Printf.printf "(%c, %c) " a b) graph.edges;
  print_newline ()

(* let () = List.iter print_graph all_spanning_trees *)

(* ******************************************************************************************** *)

(* Construct the Minimal Spanning Tree Prims's algorithm *)

type ('a, 'b) labeled_graph = {
  nodes: 'a list;
  labeled_edges : ('a * 'a * 'b) list;
}

(* binary heap *)
module PQ = struct 
  type 'a t = ('a * int) list ref 

  let create () = ref []

  let insert pq x priority = 
    pq := (x, priority) :: !pq;
    pq := List.sort (fun (_, p1) (_, p2) -> compare p1 p2) !pq

  let extract_min pq = 
    match !pq with 
     | [] -> failwith "Prioity queue is empty"
     | (x, _) :: xs -> 
      pq := xs;
      x
end

(* MST Prim's algorithm *)
let ms_tree graph = 
  let pq = PQ.create () in 
  let start_node = List.hd graph.nodes in 
  let visited = Hashtbl.create (List.length graph.nodes) in 
  let mst_edges = ref [] in 

  let add_edges node =
    List.iter (fun (u, v, w) -> 
      if u = node && not (Hashtbl.mem visited v) then PQ.insert pq (u, v, w) w 
      else if v = node && not (Hashtbl.mem visited v) then PQ.insert pq (u, v, w) w 
      ) graph.labeled_edges
  in
  
  Hashtbl.add visited start_node ();
  add_edges start_node;

  while List.length !mst_edges < List.length graph.nodes - 1 do 
    let (u, v, w) = PQ.extract_min pq in 
    if not (Hashtbl.mem visited v) then begin 
      Hashtbl.add visited v ();
      mst_edges := (u, v, w) :: !mst_edges;
      add_edges v 
    end else if not (Hashtbl.mem visited u) then begin
      Hashtbl.add visited u ();
      mst_edges := (u, v, w) :: !mst_edges;
      add_edges u 
    end
  done;

  { nodes = graph.nodes; labeled_edges = !mst_edges }


let g = { nodes = ['a'; 'b'; 'c'; 'd'; 'e'; 'f'; 'g'; 'h'];
          labeled_edges = [('a', 'b', 5); ('a', 'd', 3); ('b', 'c', 2);
                          ('b', 'e', 4); ('c', 'e', 6); ('d', 'e', 7);
                          ('d', 'f', 4); ('d', 'g', 3); ('e', 'h', 5);
                          ('f', 'g', 4); ('g', 'h', 1)] }

let mst = ms_tree g 

let print_labeled_graph graph = 
  Printf.printf "\nMinimum spanning tree\n";
  List.iter (fun (a, b, w) -> Printf.printf "(%c, %c, %d) " a b w) graph.labeled_edges;
  print_newline ()

let () = print_labeled_graph mst


(* ******************************************************************************************** *)
                                  (* Graph Isomorphism *)
                                 
type 'a graph_term = {nodes : 'a list; edges : ('a * 'a) list}

(* function to check if two sets of edges are equal *)
  let edges_equal edges1 edges2 = 
    let sorted_edges1 = List.sort compare edges1 in 
    let sorted_edges2 = List.sort compare edges2 in 
    sorted_edges1 = sorted_edges2

(* Generate all permutations of a list *)
let rec permutations lst = 
  let rec insert_all_positions x = function 
    | [] -> [[x]]
    | h :: t -> 
      (x :: h :: t) :: (List.map (fun l -> h :: l) (insert_all_positions x t ))
  in
  match lst with 
    | []  -> [[]]
    | h :: t -> 
      let perms = permutations t in 
      List.concat (List.map (insert_all_positions h) perms)

(* Apply a permutation to the nodes and transform the edges *)
let apply_permutations perm nodes edges = 
  let node_map = List.combine nodes perm in 
  let find_mapping n = List.assoc n node_map in 
  List.map (fun (u, v) -> (find_mapping u, find_mapping v)) edges

(* Check if two graphs are isomorphic *)
  let is_isomorphic g1 g2 = 
    if List.length g1.nodes <> List.length g2.nodes || List.length g1.edges <> List.length g2.edges
      then 
        false
    else
      let perms = permutations g1.nodes in 
      List.exists (fun perm -> 
        let transformed_edges = apply_permutations perm g1.nodes g1.edges in 
        edges_equal transformed_edges g2.edges
        ) perms

let g1 = {nodes = [1; 2; 3; 4; 5; 6; 7; 8];
        edges = [(1, 5); (1, 6); (1, 7); (2, 5); (2, 6); (2, 8); (3, 5);
                 (3, 7); (3, 8); (4, 6); (4, 7); (4, 8)]}

let g2 = {nodes = [5; 6; 7; 8; 1; 2; 3; 4];
        edges = [(5, 1); (5, 2); (5, 3); (6, 1); (6, 2); (6, 4); (7, 1);
                 (7, 3); (7, 4); (8, 2); (8, 3); (8, 4)]}

let () = 
  Printf.printf "\nGraph Isomorphism\n";
  if is_isomorphic g1 g2 then 
    Printf.printf "The graphs are isomorphic\n"
  else
    Printf.printf "The graphs are not isomorphic\n"


(* ******************************************************************************************** *)
                                  (* Breadth-first search *)


(* Helper function to get neighbors of a node with a condition *)
let neighbors g a cond = 
  let edge l (b, c) = 
    if b = a && cond c then c :: l
    else if c = a && cond b then b :: l
    else l
  in 
  List.fold_left edge [] g.edges

let bfs graph start_node = 
  let visited = Hashtbl.create (List.length graph.nodes) in 
  let q = Queue.create () in 
  Queue.add start_node q; 
  Hashtbl.add visited start_node ();

  let rec bfs_aux () = 
    if Queue.is_empty q then []
    else
      let node = Queue.take q in 
      let node_neighbors = neighbors graph node (fun n -> not (Hashtbl.mem visited n)) in 
      List.iter (fun neighbor ->  
          Hashtbl.add visited neighbor (); 
          Queue.add neighbor q 
      ) node_neighbors;
      node :: bfs_aux ()
  in
  bfs_aux ()

let g = {nodes = [1; 2; 3; 4; 5; 6; 7; 8];
          edges = [(1, 5); (1, 6); (1, 7); (2, 5); (2, 6); (2, 8); (3, 5);
                    (3, 7); (3, 8); (4, 6); (4, 7); (4, 8)]}

let () = 
  Printf.printf "\n Breath-first search\n";
  let bfs_result = bfs g 1 in 
  List.iter (Printf.printf "%d ") bfs_result;
  print_newline ()

(* ******************************************************************************************** *)
                                (* Depth-first search *)

let dfs graph start_node = 
  let visited = Hashtbl.create (List.length graph.nodes) in 

  let rec dfs_aux node = 
    if Hashtbl.mem visited node then []
    else begin
      Hashtbl.add visited node ();
      node :: List.concat (List.map (dfs_aux) (neighbors graph node (fun n -> not (Hashtbl.mem visited n))))
    end
  in 
  dfs_aux start_node

let () = 
  Printf.printf "\nDepth-first search\n";
  let dfs_result = dfs g 1 in 
  List.iter (Printf.printf "%d ") dfs_result;
  print_newline ()

(* ******************************************************************************************** *)
                              (* Node Degree and Graph Coloration *)

              (* The degree of a node in a graph is the number of edges connected to it. *)

type 'a graph_term = { nodes : 'a list; edges : ('a * 'a) list}

let degree graph node = 
  List.fold_left (fun acc (u, v) -> if u = node || v = node then acc + 1 else acc) 0 graph.edges

let g = {nodes = [1; 2; 3; 4; 5; 6; 7; 8];
          edges = [(1, 5); (1, 6); (1, 7); (2, 5); (2, 6); (2, 8); (3, 5);
                    (3, 7); (3, 8); (4, 6); (4, 7); (4, 8)]}

let () = 
  Printf.printf "\nDegree of node 1: %d\n" (degree g 1)


(* ******************************************************************************************** *)
                      (*  List of Nodes Sorted by Decreasing Degree *)

let nodes_sorted_by_degree graph = 
  List.sort (fun a b -> compare (degree graph b) (degree graph a)) graph.nodes

let () = 
  Printf.printf "\nNodes sorted by decreasing degree: ";
  let sorted_nodes = nodes_sorted_by_degree g in
  List.iter (Printf.printf "%d ") sorted_nodes;
  print_newline ()


(* ******************************************************************************************** *)
                      (* Welsh-Powell Algorithm for Graph Coloring *)

let g_color = {nodes = [1;  2; 3; 4; 5; 6; 7; 8]; 
               edges = [(1, 6); (1, 7); (1, 8); (2, 5); (2,7); (2,8); 
                       (3, 5); (3,6); (3,8); (4,5); (4,6); (4,7)]}

(* Function to check if a node can be colored with a given color *)
let can_color node color graph coloring = 
  List.for_all (fun (u, v) -> 
    if u = node then not (List.mem_assoc v coloring && List.assoc v coloring = color)
    else if v = node then not (List.mem_assoc u coloring && List.assoc u coloring = color) 
    else true 
    ) graph.edges

(* Welsh-Powell algorithm to color the graph *)
let welsh_powell graph = 
  let sorted_nodes = nodes_sorted_by_degree graph in 
  let rec color_nodes nodes coloring color = 
    match nodes with 
      | [] -> coloring 
      | n :: ns -> 
        if can_color n color graph coloring then 
          color_nodes ns ((n, color) :: coloring) color 
        else
          color_nodes ns coloring color 
  in
  let rec assig_colors nodes coloring current_color = 
    match nodes with 
      | [] -> coloring 
      | _ -> 
        let new_coloring = color_nodes nodes coloring current_color in 
        let remaining_nodes = List.filter (fun n -> not (List.mem_assoc n new_coloring)) nodes in 
        assig_colors remaining_nodes new_coloring (current_color + 1)
  in
  assig_colors sorted_nodes [] 0   

let () = 
  let coloring = welsh_powell g_color in 
  Printf.printf "\nNode coloring:\n";
  List.iter (fun (node, color) -> Printf.printf "Node %d -> Color %d\n" node color) coloring 

(* ******************************************************************************************** *)
                                (* Depth-First Order Graph Traversal *)

Module M : Graph = struct 

  module Char_map = Map.Make (Char)
  type node = Char
  type t = (node_list) Char_map.t 

  let of_adjacency l = 
    List.fold_right (fun (x, y) -> Char_map.add x y) l Char_map.empty 

  type colors = White | Gray | Black

  type 'a state =  {
    d : int Char_map t; (*discovery time*)
    f : int Char_map t; (*finishing time*)
    pred : char CharMap t; (*predecessor*)
    color : colors Char_map t; (*vertex colors*)
    acc : 'a; (*user specified type used by 'fold'*)
  }

  let dfs_fold g c fn acc = 
    let rec dfs_visit t u {d; f; pred; color; acc} = 
      let edge (t, state) v = 
        if Char_map.find v state.color = White then 
          dfs_visit t v {state with pred = Char_map.add v u state.pred}
      else (t, state)
    in
    let t, {d; f; pred; color; acc} = 
      let t = t + 1 in 
      List.fold_left edge 
        (t, {d = Char_map.add u t d; f; 
              pred; color = Char_map.add u Gray color; acc = fn acc u })
        (Char_map.find u g)
    in
    let t = t + 1 in 
    t, {d; f = Char_map.add u t f; pred; 
          color = Char_map.add u Black color; acc}
    in
    let v = List.fold_left (fun k (x, _ ) -> x :: k) []
                            (Char_map.bindings g) in 
    let initial_state = 
      {d = Char_map.empty;
       f = Char_map.empty; 
       pred = Char_map.empty; 
       color = List.fold_right (fun x -> Char_map.add x White)
                                v Char_map.empty;
        acc}
    in
    (snd (dfs_visit 0 c initial_state)).acc
  end;;
Module M : GRAPH


(* ******************************************************************************************** *)
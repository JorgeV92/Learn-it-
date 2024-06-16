(* 
 _______  ______ _______ _______ _______
    |    |_____/ |______ |______ |______
    |    |    \_ |______ |______ ______|
                                       

    0226. Invert Binary Tree    (Easy)

    Given the root of a binary tree, invert the tree, and return its root.

    Example 1:

    Input: root = [4,2,7,1,3,6,9]
    Output: [4,7,2,9,6,3,1]

    Example 2:

    Input: root = [2,1,3]
    Output: [2,3,1]

    Example 3:

    Input: root = []
    Output: []   
*)

(* 
* Method recursively swap left and right children of every node in the tree. Using the method 
* of depth-first search (DFS) and breadth-first search (BFS) approach. 
*)

open Printf
open Queue

type tree_node = {
  mutable value : int;
  mutable left : tree_node option;
  mutable right : tree_node option;
}

let create_node x = 
  { value = x; left = None; right = None }

(* DFS *)
let rec invert_tree_dfs root = 
  match root with 
  | None -> None
  | Some node -> 
    (* Swap the left and right children *)
    let temp = node.left in 
    node.left <- node.right;
    node.right <- temp;
    (* Recurse *)
    node.left <- invert_tree_dfs node.left;
    node.right <- invert_tree_dfs node.right;
    Some node

(* BFS *)
let invert_tree_bfs root = 
  match root with 
  | None -> None
  | Some node -> 
    let q = Queue.create () in 
    Queue.add node q;
    while not (Queue.is_empty q) do 
      let current = Queue.take q in 
      (* Swap the left and right children *)
      let temp = current.left in 
      current.left <- current.right;
      current.right <- temp;
      (match current.left with 
        | Some l -> Queue.add l q 
        | None -> ());
      (match current.right with 
        | Some r -> Queue.add r q 
        | None -> ())
    done;
    Some node

let print_tree root = 
  match root with 
  | None -> ()
  | Some node -> 
    let q = Queue.create () in 
    Queue.add node q;
    while not (Queue.is_empty q) do 
      let current = Queue.take q in 
      printf "%d" current.value;
      (match current.left with 
        | Some l -> Queue.add l q
        | None -> ());
      (match current.right with 
        | Some r -> Queue.add r q 
        | None -> ())
    done;
    printf "\n"

let () = 
    (* Example 1: Input: root = [4, 2, 7, 1, 3, 6, 9] *)
    let root1 = Some { value = 4; left = Some { value = 2; left = Some { value = 1; left = None; right = None }; 
                right = Some { value = 3; left = None; right = None } }; right = Some { value = 7; left = Some 
                { value = 6; left = None; right = None }; right = Some { value = 9; left = None; right = None } } } in
    printf "Original tree 1: ";
    print_tree root1;
    let inverted1 = invert_tree_bfs root1 in
    printf "Inverted tree 1: ";
    print_tree inverted1;

  (* Example 2: Input: root = [2,1,3] *)
  let root2 = Some { value = 2; left = Some { value = 1; left = None; right = None }; right = Some { value = 3; left = None; right = None } } in
  printf "Original tree 2: ";
  print_tree root2;
  let inverted2 = invert_tree_bfs root2 in
  printf "Inverted tree 2: ";
  print_tree inverted2;

  (* Example 3: Input: root = [] *)
  let root3 = None in
  printf "Original tree 3: ";
  print_tree root3;
  let inverted3 = invert_tree_bfs root3 in
  printf "Inverted tree 3: ";
  print_tree inverted3

      

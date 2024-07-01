type 'a tree =
  | Leaf
  | Node of 'a node
and 'a node = {
  value : 'a;
  mutable left : 'a tree;
  mutable right : 'a tree;
  mutable parent : 'a tree;
}

(* Function to find the minimum value in a subtree *)
let rec bst_minimum t =
  match t with
  | Leaf -> Leaf
  | Node { left = Leaf; _ } -> t
  | Node { left; _ } -> bst_minimum left

let rec bst_maximum t = 
  match t with 
    | Leaf -> Leaf
    | Node {right = Leaf; _ } -> t
    | Node {right; _ } -> bst_maximum right 

let bst_predecessor x =
    match x with
    | Leaf -> Leaf
    | Node n ->
      if n.left <> Leaf then
        bst_maximum n.left
      else
        let rec find_predecessor x y =
          match y with
          | Leaf -> Leaf
          | Node y_node ->
            if x == y_node.left then
              find_predecessor y y_node.parent
            else
              y
        in
        find_predecessor x n.parent

(* Function to find the successor of a given node *)
let bst_successor x =
  match x with
  | Leaf -> Leaf
  | Node n ->
    if n.right <> Leaf then
      bst_minimum n.right
    else
      let rec find_successor x y =
        match y with
        | Leaf -> Leaf
        | Node y_node ->
          if x = y_node.right then
            find_successor y y_node.parent
          else
            y
      in
      find_successor x n.parent


(* Example usage *)
let create_node value left right parent =
  Node { value; left; right; parent }

let example_tree () =
  let leaf = Leaf in
  let node3 = create_node 3 leaf leaf leaf in
  let node7 = create_node 7 leaf leaf leaf in
  let node5 = create_node 5 node3 node7 leaf in
  let node20 = create_node 20 leaf leaf leaf in
  let node15 = create_node 15 node5 node20 leaf in
  (match node3 with Node n -> n.parent <- node5 | _ -> ());
  (match node7 with Node n -> n.parent <- node5 | _ -> ());
  (match node5 with Node n -> n.parent <- node15 | _ -> ());
  (match node20 with Node n -> n.parent <- node15 | _ -> ());
  node15

let () =
  let root = example_tree () in
  let successor =
    match bst_successor root with
    | Leaf -> "None"
    | Node n -> string_of_int n.value
  in
  Printf.printf "The successor is: %s\n" successor
        
  
let () =
  let root = example_tree () in
  let predecessor =
    match bst_predecessor root with
    | Leaf -> "None"
    | Node n -> string_of_int n.value
  in
  Printf.printf "The predecessor is: %s\n" predecessor


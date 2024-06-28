type 'a binary_tree = 
  | Empty 
  | Node of 'a * 'a binary_tree * 'a binary_tree

(* Example of tree carrying char data *)
let example_tree = 
  Node ('a', Node ('b', Node ('d', Empty, Empty), Node ('e', Empty, Empty)), 
        Node ('c', Empty, Node ('f', Node ('g', Empty, Empty), Empty)))

(* Write a function cbal_tree to construct completely balanced binary trees for a 
   given number of nodes. The function should generate all solutions via backtracking. 
   Put the letter 'x' as information into all nodes of the tree. *)

(* A completely balanced binary tree is defined as a tree in which the difference between the 
   heights of the left and right subtrees is at most 1 for every node.  *)

(* Function to generate completely balanced binary tree with a given number of nodes *)
let rec cbal_tree n =  
  if n = 0 then [Empty]
  (* Even *)
  else if n mod 2 = 1 then 
    let t = cbal_tree (n / 2) in 
    List.concat (List.map (fun left -> List.map (fun right ->  Node ('x', left, right)) t) t)
  else
    (* Odd *)
    let t1 = cbal_tree (n / 2 - 1) in 
    let t2 = cbal_tree (n / 2) in 
    List.concat  [
      List.concat (List.map (fun left -> List.map (fun right -> Node ('x', left, right)) t1) t2);
      List.concat (List.map (fun left -> List.map (fun right ->  Node ('x', left, right)) t2) t1)
    ] 

let () = 
    let trees = cbal_tree 4 in 
    List.iter (fun tree -> 
      let rec print_tree = function 
        | Empty -> print_string "Empty"
        | Node (x, l, r) -> 
          Printf.printf "Node('%c', " x;
          print_tree l;
          print_string " ";
          print_tree r;
          print_string ")"
      in
      print_tree tree;
      print_newline ()
    ) trees 


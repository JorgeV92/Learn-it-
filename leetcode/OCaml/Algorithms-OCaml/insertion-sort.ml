(* 
    Insertion sort    
*)

(* insertion into a sorted list *)

let rec insert elem lst = 
  | [] -> [elem]
  | hd :: tl -> if elem < hd then elem :: lst
                else hd :: insert elem tl  
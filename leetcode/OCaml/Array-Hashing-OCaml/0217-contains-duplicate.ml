(*
  0217. Contains Duplicate  (Easy)

  Given an integer array nums, return true if any value appears at least twice in the array, and 
  return false if every element is distince.

  Example 1:

  Input: nums = [1,2,3,1]
  Output: true
*)

let containsDuplicate nums = 
  (* A module implementation of a set that uses integers *)
  let module IntSet = Set.Make(struct type t = int let compare = compare end) in 
  let rec aux set = function 
    | [] -> false
    | x :: xs -> 
        if IntSet.mem x set then true
        else aux (IntSet.add x set) xs
      in 
       aux IntSet.empty nums

(* Examale usage *)
let () = 
      let nums1 = [1; 2; 3; 1] in 
      let nums2 = [1; 2; 3; 4] in
      Printf.printf "%b\n" (containsDuplicate nums1);
      Printf.printf "%b\n" (containsDuplicate nums2);
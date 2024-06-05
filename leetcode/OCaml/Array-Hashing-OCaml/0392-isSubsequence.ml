(* 
  0392. Is Subsequence (Easy)
  
  Given two stirngs s and t, return true if s is a subsequence of t, or false otherwise.

  A subsequence of a string is a new string that is formed from the original string by deleting some
  (can be none) of the characters without disturbing the relative positions of the remaining characters.

  Example 1:

  Input: s = "abc", t = "ahbgdc"
  Output: true
*)

let isSubsequence s t = 
  let rec aux s_idx t_idx = 
   if s_idx = String.length s then true 
   else if t_idx = String.length t then false
   else if s.[s_idx] = t.[t_idx] then aux (s_idx + 1) (t_idx + 1)
   else aux s_idx (t_idx + 1)
  in 
  aux 0 0

(* Example usage *)
let () =
  let s1 = "abc" in 
  let t1 = "ahbgdc" in
  Printf.printf "%b\n" (isSubsequence s1 t1);
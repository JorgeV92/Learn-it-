(* 
  0704. Binary Search 
  
  Given an array of integers nums which is sorted in ascending order, and an integer target, write a 
  function to search target in nums. If target exists, then return its index. Otherwise, return -1

  Example 1:

  Input: nums = [-1,0,3,5,9,12], target = 9
  Output: 4
  Explanation: 9 exists in nums and its index is 4
*)

let binarySearch nums target = 
  let rec aux left right = 
    if left > right then -1 
    else 
      let mid = left + (right - left) / 2 in 
      if nums.(mid) = target then mid
      else if nums.(mid) < target then aux (mid + 1) right 
      else aux left (mid - 1) 
    in 
    aux 0 (Array.length nums - 1)


(* Example usage *)
let () = 
    let nums = [| -1; 0; 3; 5; 9; 12 |] in 
    let target = 9 in 
    Printf.printf "%d\n" (binarySearch nums target)

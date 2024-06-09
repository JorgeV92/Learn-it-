(* 
  You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. 
  All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, 
  adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were 
    broken into on the same night.

  Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob 
  tonight without alerting the police.

  
  Example 1:

  Input: nums = [2,3,2]
  Output: 3
  Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.   
*)

let rob_linear nums = 
  let n = Array.length nums in 
  let rec aux_rob_from i rob not_rob = 
    if i >= n then max rob not_rob 
    else 
      let new_rob = not_rob + nums.(i) in 
      let new_not_rob = max rob not_rob in 
      aux_rob_from (i + 1) new_rob new_not_rob 
    in 
    aux_rob_from 0 0 0 

let rob nums = 
  let n = Array.length nums in 
  if n = 0 then 0 
  else if n = 1 then nums.(0) 
  else 
    let nums1 = Array.sub nums 0 (n - 1) in 
    let nums2 = Array.sub nums 1 (n - 1) in 
    max (rob_linear nums1) (rob_linear nums2)

let () =
    let test nums expcted = 
      let result = rob (Array.of_list nums) in 
      Printf.printf "rob %s = %d (expected %d)\n" 
        (String.concat "," (List.map string_of_int nums)) result expcted 
    in 
    test [2; 3; 2] 3;
    test [1; 2; 3; 1] 4;
    test [1; 2; 3] 3;
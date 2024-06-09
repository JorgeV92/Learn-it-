(* 
  You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, 
  the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it 
  will automatically contact the police if two adjacent houses were broken into on the same night.

  Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob 
  tonight without alerting the police.

  

  Example 1:

  Input: nums = [1,2,3,1]
  Output: 4
  Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
  Total amount you can rob = 1 + 3 = 4. 
*)

let rob nums = 
  let n = Array.length nums in 
  let rec aux i rob not_rob = 
    if i >= n then max rob not_rob 
    else 
      let new_rob = not_rob + nums.(i) in 
      let new_not_rob = max not_rob rob in 
      aux (i + 1) new_rob new_not_rob
    in
    aux 0 0 0 

let rob_with_array nums =
  let n = Array.length nums in 
  if n = 0 then 0 
  else if n = 1 then nums.(0) 
  else 
    let maxRobbedAmount = Array.make n 0 in 
    maxRobbedAmount.(0) <- nums.(0);
    maxRobbedAmount.(1) <- max nums.(0) nums.(1);
    for i = 2 to n - 1 do
      maxRobbedAmount.(i) <- max maxRobbedAmount.(i - 1) (maxRobbedAmount.(i - 2) + nums.(i))
    done;
    maxRobbedAmount.(n - 1)

let () = 
let test nums expected = 
  let result = rob_with_array (Array.of_list nums) in 
  Printf.printf "rob %s = %d (expected %d)\n" 
    (String.concat "," (List.map string_of_int nums)) result expected
in
test [1; 2; 3; 1] 4;
test [2; 7; 9; 3; 1] 12;
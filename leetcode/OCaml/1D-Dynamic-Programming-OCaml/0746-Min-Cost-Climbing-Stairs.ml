(* 
    You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you 
    pay the cost, you can either climb one or two steps. 

    You can either start from the step with index 0, or the step with index 1

    Return the minimum cost to reach the top of the floor.

    Example 1:

    Input: cost = [10,15,20]
    Output: 15
    Explanation: You will start at index 1.
    - Pay 15 and climb two steps to reach the top.
    The total cost is 15.
*)

let min_cost_climbing_stairs cost = 
  let n = Array.length cost in 
  if n = 0 then 0 
  else if n = 1 then cost.(0) 
  else 
    let min_cost = Array.make (n) 0 in
    min_cost.(0) <- cost.(0);
    min_cost.(1) <- cost.(1);
    for i = 2 to n - 1 do 
      min_cost.(i) <- cost.(i) + min min_cost.(i - 1) min_cost.(i - 2)
    done;
    min min_cost.(n - 1) min_cost.(n - 2)



let () = 
  let test cost expected = 
    let result = min_cost_climbing_stairs (Array.of_list cost) in 
    Printf.printf "min_cost_climbing_stairs %s = %d (expected %d)\n" 
      (String.concat "," (List.map string_of_int cost)) result expected
  in 
  test [10; 15; 20] 15; 
  test [1; 100; 1; 1; 1; 100; 1; 1; 100; 1] 6

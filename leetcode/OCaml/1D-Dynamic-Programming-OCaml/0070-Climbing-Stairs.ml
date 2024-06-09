(* 
  0070. Climbing Stairs (Easy)
  
  You are climbing a staircase. It takes n steps to reach the top.

  Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

  Example 1:

  Input: n = 2
  Output: 2
  Explanation: There are two ways to climb to the top.
  1. 1 step + 1 step
  2. 2 steps
*)

let climbingStairs n = 
  if n <= 1 then 1
  else if n = 2 then 2
  else 
    let rec aux i prev1 prev2 = 
      if i > n then prev2
      else 
        let current = prev1 + prev2 in 
        aux (i + 1) prev2 current
      in 
      aux 3 1 2

let climbingStairsDP n = 
    let waysToClimb = Array.make (n + 1) 0 in 
    waysToClimb.(0) <- 1; 
    waysToClimb.(1) <- 1;
    for i = 2  to n do 
      waysToClimb.(i) <- waysToClimb.(i - 1) + waysToClimb.(i - 2)
    done; 
    waysToClimb.(n)

let () = 
    let test n expected = 
      let result = climbingStairs n in 
      Printf.printf "Climb stairs original %d = %d (exptected %d)\n" n result expected
    in 
    test 2 2; 
    test 3 3;
    test 4 5;
    test 5 8



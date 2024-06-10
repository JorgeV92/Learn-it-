(* 
  
    0322. Coin Change (Medium)

    You are given an integer array coins representing of different denominations and an integer
    amount representing a total amount of money.

    Return the fewest number of coins that you need to make up that amount. If that amount of money 
    cannot be made up by any combination of the coins, return -1.


    Example 1:

    Input: coins = [1,2,5], amount = 11
    Output: 3
    Explanation: 11 = 5 + 5 + 1

    Example 2:

    Input: coins = [2], amount = 3
    Output: -1
    Example 3:

    Input: coins = [1], amount = 0
    Output: 0
   
*)

let coin_change coins amount = 
  (* If the amount is 0, no coins are needed *)
  if amount = 0 then 0 
  else 
    (* An array to store the the minimum number of coins for each amount up tp the given amount *)
    let min_coins = Array.make (amount + 1) max_int in 
    (* Base case: 0 coins are needed to make amount 0 *)
    min_coins.(0) <- 0;

    (* for all amount from 1 to given amount *)
    for i = 1 to amount do 
      (* check each coin *)
      List.iter (fun coin -> 
        (* if the coin is less than or equal to the current amount and the sub-amount is not 
        infinite *)
        if coin <= i && min_coins.(i - coin) <> max_int then 
          (* update the min_coins array with the minimum number of coins needed *)
          min_coins.(i) <- min min_coins.(i) (min_coins.(i - coin) + 1) 
        ) coins
    done;

    (* return the result: if the amount is not reachable, return -1, otherwise return min_coins 
       for the amount *)
    if min_coins.(amount) = max_int then -1 else min_coins.(amount)


let () = 
  let test coins amount expected = 
    let result = coin_change coins amount in 
    Printf.printf "Fewest coins neeeded for amount %d: %d (expected %d)\n" amount result expected 
  in 
  test [1; 2; 5] 11 3;
  test [2] 3 (-1);
  test[1] 0 0; 
  test [1; 2; 5] 7 2
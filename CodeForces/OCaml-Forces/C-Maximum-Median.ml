(* 
                                C. Maximum Median
    
    You are given an array 𝑎 of 𝑛 integers, where 𝑛 is odd. You can make the following operation with it:
    
    Choose one of the elements of the array (for example 𝑎𝑖 ) and increase it by 1 (that is, replace it with 𝑎𝑖+1).
    You want to make the median of the array the largest possible using at most 𝑘 operations.
    
    The median of the odd-sized array is the middle element after the array is sorted in non-decreasing order. 
    For example, the median of the array [1,5,2,3,5] is 3.
    
    Input
    The first line contains two integers 𝑛 and 𝑘 (1 ≤ 𝑛 ≤ 2⋅10^5, 𝑛 is odd, 1 ≤ 𝑘 ≤ 10^9) — 
    the number of elements in the array and the largest number of operations you can make.
    
    The second line contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (1 ≤ 𝑎𝑖 ≤ 10^9).
    
    Output
    Print a single integer — the maximum possible median after the operations.

    Example
    input 
    3 2
    1 3 5

    output
    5   
*)

open Printf

let () = 
  let read_int_array str =
    str 
      |> String.split_on_char ' '
      |> Array.of_list
      |> Array.map int_of_string
  in

  let num_line = input_line stdin in 
  let n, k = 
    match String.split_on_char ' ' num_line with 
      | [n1; n2] -> (int_of_string n1, int_of_string n2)
      | _ -> failwith "Expected exactly two numbers"
  in
  
  let a = read_int_array (input_line stdin) in 
  Array.sort compare a; 

  let good x = 
    let ops_needed = ref 0 in 
    for i = (n - 1) / 2 to n - 1 do 
      ops_needed := !ops_needed +  max 0 (x - a.(i));
    done;
    !ops_needed <= k
  in 
  
  let rec binary_search l r = 
    if l < r then 
      let m = l + (r - l + 1) / 2 in 
      if good m then 
        binary_search m r 
      else
        binary_search l (m - 1)
    else
      l 
  in
  let procedure = binary_search 0 (2 * 1_000_000_000) in 
  printf "%d\n" procedure



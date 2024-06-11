(* 
   0091. Decode Ways (Medium)

    A message containing letters form A-Z can be encoded into numbers using the following mapping;

        'A' -> "1"
        'B' -> "2"
            .
            .
            .
        'Z' -> "26"

    To decode an encoded message, all the digits must be grouped then mapped back into letters using 
    the reverse of the mapping above (there may be multiple ways). For exampke "11106" can be mapped into:

        - "AAJf" with grouping [1 1 10 6]
        - "KJF" with grouping [11 10 6] 

    Note that the grouping [1 11 06] is invalid because "06" cannot be mapped into 'F' sine "6" is 
    different from "06".

    Given a string s containing only digits, return the number of ways to decode it. 

    Example 1:

    Input: s = "12"
    Output: 2
    Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).   
*)

let num_decodings s = 
  (* if the string is empty or starts with 0 return 0 *)
    if String.length s = 0 || s.[0] = '0' then 0
    else 
      let n = String.length s in 

      (* Array to store the number of ways to decode each substring *)
      let decodings = Array.make (n + 1) 0 in 

      (* Base cases *)
      decodings.(0) <- 1;    (* There is one way to decode an empty string *)
      decodings.(1) <- 1;    (* There is one way to decode a string of length 1 if it's not a 0 *)
      
        (* iterate through the string starting from the second character *)
        for i = 2 to n do 
          (* check the last single digit *)
          if s.[i - 1] <> '0' then 
            decodings.(i) <- decodings.(i) + decodings.(i - 1);

          (* check the last two digits *)
          let two_digits = int_of_string (String.sub s (i - 2) 2) in 
          if two_digits >= 10 && two_digits <= 26 then 
            decodings.(i) <- decodings.(i) + decodings.(i - 2)
        done;

        (* Return the number of ways to decode the entire stirng  *)
        decodings.(n)

let () =
  let test s expected = 
    let result = num_decodings s in 
    Printf.printf "num_decodings \"%s\" = %d (expected %d)\n" s result expected 
  in 
  test "12" 2;
  test "226" 3;
  test "06" 0

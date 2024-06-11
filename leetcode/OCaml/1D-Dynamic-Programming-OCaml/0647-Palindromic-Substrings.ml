(* 
   Given a string s, return the number of palindromic substrings in it. (Medium)

    A string is a palindrome when it reads the same backward as forward.

    A substring is a contiguous sequence of characters within the string.

 

    Example 1:

    Input: s = "abc"
    Output: 3
    Explanation: Three palindromic strings: "a", "b", "c".
*)

let count_substrings s = 
  let len = String.length s in 
  let count = ref 0 in 

  (* Function to expand around the center and count palindromes *)
  let expand_around_center left right = 
    let rec expand left right = 
      if left >= 0 && right < len && s.[left] = s.[right] then 
        begin
        incr count;   (* found a palindrome substring, increment the count *)
        expand (left - 1) (right + 1)
        end
      in
        expand left right 
    in 

    (* loop through each character and its gap with the next character *)
    for i = 0 to len - 1 do 
      expand_around_center i i;         (* Odd length palindromes (single character) *)
      expand_around_center i (i + 1);   (* Even length palindromes (center is between i and i + 1) *)
    done;
    !count (* Return the total count of palindromic substrings *)


let count_substrings_dp s = 
  let n = String.length s in 
  let palindrome = Array.make_matrix n n false in 
  let count = ref 0 in 

  (* Loop over possible lengths of substrings *)
  for len = 1 to n do 
    (* loop over possible starting indices of substrings *)
    for i = 0 to n - len do
      let j = i + len - 1 in 
      (* check if the substring s[i..j] is a palindrome *)
        if s.[i] = s.[j] && (len <= 2 || palindrome.(i + 1).(j - 1)) then 
          begin
            palindrome.(i).(j) <- true;
            incr count 
          end
        done
      done;
      !count (* Return the total count of palindromic substrings *)

      
let () = 
    let test s expected = 
      let result = count_substrings_dp s in 
      Printf.printf "count_substrings \"%s\" = %d (expected %d)\n" s result expected 
    in 
    test "abc" 3;
    test "aaa" 6
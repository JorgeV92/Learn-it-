(* 
  0005. Longest Palindromic Substring (Medium)
  
  Given a string s, return the longest palindromic substring in s.

  Example 1:

  Input: s = "babad"
  Output: "bab"
  Explanation: "aba" is also a valid answer.
*)

let longest_palindrome_center s =
  let len = String.length s in 
  if len = 0 then "" 
  else 
    let expand_around_center left right = 
      let rec expand left right = 
        if left >= 0 && right < len && s.[left] = s.[right] then 
          expand (left - 1) (right + 1)
        else
          right - left - 1
        in
        expand left right 
      in
      
      let rec find_longest start end_ i = 
        if i >= len then String.sub s start (end_ - start + 1)
        else
          let len1 = expand_around_center i i in 
          let len2 = expand_around_center i (i + 1) in 
          let len = max len1 len2 in 
          if len > end_ - start then 
            let new_start = i - (len - 1) / 2 in 
            let new_end = i + len / 2 in 
            find_longest new_start new_end (i + 1)
          else    
            find_longest start end_ (i + 1)
          in
          find_longest 0 0 0 


let longest_palindrome_dp s  =
  let len = String.length s in 
  if len <= 1 then s 
  else 
    let is_palindrome = Array.make_matrix len len false  in
    let max_length = ref 1 in 
    let start_index = ref 0 in
    let end_index = ref 0 in 
    
    (* All substrings of length 1 are palindromes *)
    for i = 0 to len - 1 do
      is_palindrome.(i).(i) <- true 
    done;

    (* check for substring of length greater than 1 *)
    for i = 1 to len -  1 do
      for j = 0 to i - 1 do
        if s.[j] = s.[i] && (i - j <= 2 || is_palindrome.(j + 1).(i - 1)) then 
          begin
            is_palindrome.(j).(i) <- true;
            if i - j + 1 > !max_length then 
            begin
              max_length := i - j + 1;
              start_index := j;
              end_index := i 
            end 
        end
      done
    done;
    String.sub s !start_index (!end_index - !start_index + 1)

let () = 
  let test s expected = 
    let result = longest_palindrome_center s in 
    Printf.printf "longest_palindrome_center \"%s\" = \"%s\" (expected \"%s\")\n" s result expected 
  in
    test "babad" "aba";
    test "cbbd" "bb"

let () = 
  let test s expected = 
    let result = longest_palindrome_dp s in 
    Printf.printf "longest_palindrome_dp \"%s\" = \"%s\" (expected \"%s\")\n" s result expected
  in
  test "babad" "aba";
  test "cbbd" "bb"
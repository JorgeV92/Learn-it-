(* 
    0139. Word Break    (Medium) 

    Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a
    space-separated sequence of one or more dictionary words. 

    Example 1:

    Input: s = "leetcode", wordDict = ["leet","code"]
    Output: true
    Explanation: Return true because "leetcode" can be segmented as "leet code".
    Example 2:

    Input: s = "applepenapple", wordDict = ["apple","pen"]
    Output: true
    Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
    Note that you are allowed to reuse a dictionary word.
    Example 3:

    Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    Output: false 
*)

let set_of_list lst = 
  let set = Hashtbl.create (List.length lst) in 
  List.iter (fun x -> Hashtbl.add set x ()) lst;
  set 

let word_break s word_dict = 
  (* convert the word dictionary list into a set for quick lookup *)
  let word_set = set_of_list word_dict in 

  (* array to store if the substring up to each position can be segemented *)
  let can_segment = Array.make (String.length s + 1) false in 

  (* Base case: an empty string can be segmented *)
  can_segment.(0) <- true;
  
  (* for all substrings of s *)
  for i = 1 to String.length s do
     (* check all possible ending positions of the current substring *)
     for j = 0 to i - 1 do 
      (* if the substring [j:i] is in the word set and can_segment[j] is true *)
        let sub = String.sub s j (i - j) in 
        if can_segment.(j) && Hashtbl.mem word_set sub then 
          can_segment.(i) <- true
      done
    done;

    (* Return whether the entire string can be segmented *)
    can_segment.(String.length s)

let () = 
    let test s word_dict expected = 
      let result = word_break s word_dict in 
      Printf.printf "Can \"%s\" be segmented? %s (expected %s)\n"
        s (if result then "true" else "false") (if expected then "true" else "false")
    in 
    test "leetcode" ["leet"; "code"] true;                            (* Expected output: true *)
    test "applepenapple" ["apple"; "pen"] true;                       (* Expected output: true *)
    test "catsandog" ["cats"; "dog"; "sand"; "and"; "cat"] false      (* Expected output: false *)

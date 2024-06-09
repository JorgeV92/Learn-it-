(* 
    0200. Number of Islands 

    Given an m x n 2D binary grid `grid` which representes a map of `1`s (land) and `0`s (water),
    return the number of islands.

    As island is surrounded by water and is formed by connecting adjacent lands horizontally or 
    vertically. You may assume all four edges of the grid are all surrouneded by water. 

    Example 1:

    Input: grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
    ]
    Output: 1
*)

let num_islands_dfs grid = 
  let m = Array.length grid in 
  let n = Array.length grid.(0) in 
  let num_islands = ref 0 in 

  let rec dfs i j = 
    (* check for out-of-bounds or water cell *)
    if i < 0 || i >= m || j < 0 || j >= n || grid.(i).(j) = '0' then 
      ()
  else 
    begin
      (* Mark the cell as visited by setting it to '0' *)
      grid.(i).(j) <- '0';
      (* expand in all 4 possible directions (up, down, left, right) *)
      dfs (i + 1) j;    (* down *)
      dfs( i - 1) j;    (* up *)
      dfs i (j + 1);    (* right *)
      dfs i (j - 1);    (* left *)
    end 
  in 

  (* iterate throigh each cell in the grid *)
  for i = 0 to m - 1 do 
    for j = 0 to n - 1 do
      (* if the cell is '1' (land), we found an island *)
        if grid.(i).(j) = '1' then begin
          incr num_islands;
          dfs i j
        end
    done
  done;

  !num_islands (* Return the total number of islands *)


let num_islands_bfs grid = 
  let m = Array.length grid in 
  let n = Array.length grid.(0) in 
  let num_islands = ref 0 in 

  (* Directions array to exploare all 4 possible (down, up, right, left) *)
  let directions = [|(1, 0); (-1, 0); (0, 1); (0, -1) |] in 

  let bfs i j = 
    let queue = Queue.create () in 
    Queue.add (i, j) queue; 
    grid.(i).(j) <- '0';

    while not (Queue.is_empty queue) do 
      let (x, y) = Queue.take queue in 

      Array.iter (fun (dx, dy) -> 
        let new_x = x + dx in 
        let new_y = y + dy in 

        (* check fir valid indices and if the cell is a land '1' *)
        if new_x >= 0 && new_x < m && new_y >= 0 && new_y < n && grid.(new_x).(new_y) = '1' then begin
          grid.(new_x).(new_y) <- '0';
          Queue.add (new_x, new_y) queue;
        end
      ) directions;
    done 
  in 

  for i = 0 to m - 1 do
    for j = 0 to n - 1 do 
      if grid.(i).(j) = '1' then begin
        incr num_islands;
        bfs i j 
      end
    done
  done;
  
  !num_islands




let () = 
  let grid = [|
    [|'1'; '1'; '1'; '1'; '0'|];
    [|'1'; '1'; '0'; '1'; '0'|];
    [|'1'; '1'; '0'; '0'; '0'|];
    [|'0'; '0'; '0'; '0'; '0'|]
  |] 
  in
  let result = num_islands_bfs grid in 
  Printf.printf "num_islands_dfs = %d (expected 1)\n" result


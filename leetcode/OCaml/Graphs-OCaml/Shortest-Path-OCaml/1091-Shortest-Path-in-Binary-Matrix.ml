(* 
 _______ _     _  _____   ______ _______ _______ _______ _______       _____  _______ _______ _     _     
 |______ |_____| |     | |_____/    |    |______ |______    |         |_____] |_____|    |    |_____|     
 ______| |     | |_____| |    \_    |    |______ ______|    |         |       |     |    |    |     |     
                                                                                                       

    1091. Shortest Path in Binary Matrix    (Medium)



    Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. if 
    there is no clear path, return -1

    A clear path in a binary matrix is a path from the top-left (0, 0) to the bottom-right 
    cell (n-1, n-1) such that:

        - All the visited cells of the path are 0
        - All the adjacent cells of the path are 8-directionally connected (they are different and 
        they share an edge or a corner.)

    The length of a clear path is the number of visited cells of this path.   

*)

open Printf
open Queue 

let shortest_path_binary_matrix grid =
  let n = Array.length grid in
  if n = 0 || grid.(0).(0) <> 0 || grid.(n - 1).(n - 1) <> 0 then
    -1
  else
    let directions = [|(1, 0); (-1, 0); (0, 1); (0, -1); (1, 1); (1, -1); (-1, 1); (-1, -1)|] in
    let q = Queue.create () in
    Queue.add (0, 0) q;
    grid.(0).(0) <- 1;

    let rec bfs path_length =
      if Queue.is_empty q then
        -1
      else
        let size = Queue.length q in
        let rec process_queue size =
          if size = 0 then
            bfs (path_length + 1)
          else
            let x, y = Queue.pop q in
            if x = n - 1 && y = n - 1 then
              path_length
            else (
              Array.iter (fun (dx, dy) ->
                let new_x = x + dx in
                let new_y = y + dy in
                if new_x >= 0 && new_x < n && new_y >= 0 && new_y < n && grid.(new_x).(new_y) = 0 then begin
                  Queue.add (new_x, new_y) q;
                  grid.(new_x).(new_y) <- 1;
                end
              ) directions;
              process_queue (size - 1)
            )
        in
        process_queue size
    in
    bfs 1

let () =
  let grid1 = [|
    [|0; 1; 0|];
    [|1; 0; 0|];
    [|0; 0; 0|]
  |] in
  printf "Shortest path length in grid1: %d\n" (shortest_path_binary_matrix grid1);

  let grid2 = [|
    [|0; 1|];
    [|1; 0|]
  |] in
  printf "Shortest path length in grid2: %d\n" (shortest_path_binary_matrix grid2);

  let grid3 = [|
    [|1; 0|];
    [|0; 0|]
  |] in
  printf "Shortest path length in grid3: %d\n" (shortest_path_binary_matrix grid3);


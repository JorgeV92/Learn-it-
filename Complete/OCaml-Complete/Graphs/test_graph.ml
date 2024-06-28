type ('a, 'b) graph_type = {nodes : 'a list; edges : ('a * 'a * 'b) list}

let list_vertices graph =
  List.fold_left (fun acc (a, b, _) ->
    let acc = if List.mem b acc then acc else b::acc in
    let acc = if List.mem a acc then acc else a::acc in
    acc
  ) [] graph.edges


let neighbors graph v = 
  List.fold_left (fun acc (a, b, d) -> 
    if a = v then (b, d) :: acc else acc
    ) [] graph.edges  


let remove_from v lst = 
  let rec aux acc = function 
    | [] -> failwith "remove_from"
    | x :: xs -> 
      if x = v then List.rev_append acc xs 
      else aux (x :: acc) xs 
    in aux [] lst

let smallest_distance q dist = 
  match q with 
    | [] -> assert false 
    | x :: xs -> 
      let rec aux distance v = function 
        | y :: ys -> 
          let d = Hashtbl.find dist y in 
          if d < distance then 
            aux d y ys 
          else
            aux distance v ys 
        | [] -> (v, distance)
      in
      aux (Hashtbl.find dist x) x xs

      let dijkstra max_val zero add graph source target = 
        let vertices = list_vertices graph in 
        let dist_between u v = 
          try 
            List.find (fun (x, y, _) -> x = u && y = v) graph.edges |> (fun (_, _, d) -> d)
          with Not_found -> zero
        in 
        let dist = Hashtbl.create 1 in 
        let previous = Hashtbl.create 1 in 
        List.iter (fun v -> 
          Hashtbl.add dist v max_val
        ) vertices;
        Hashtbl.replace dist source zero;
        let rec loop = function
          | [] -> ()
          | q -> 
            let u, dist_u = smallest_distance q dist in 
            if dist_u = max_val then 
              failwith "vertex inaccessible";
            if u = target then () else begin
              let q = remove_from u q in 
              List.iter (fun (v, d) -> 
                if List.mem v q then begin
                  let alt = add dist_u d in 
                  let dist_v = Hashtbl.find dist v in 
                  if alt < dist_v then begin 
                    Hashtbl.replace dist v alt;
                    Hashtbl.replace previous v u;
                  end
                end
              ) (neighbors graph u);
              loop q 
            end
        in 
        loop vertices;
        let s = ref [] in 
        let u = ref target in 
        while Hashtbl.mem previous !u do 
          s := !u :: !s;
          u := Hashtbl.find previous !u 
        done;
        (source :: !s)

  let g = {nodes = ['a'; 'b'; 'c'; 'd'; 'e'; 'f']; 
          edges = [('a', 'c', 9); 
                  ('a', 'f', 14);
                  ('b', 'c', 10);
                  ('b', 'd', 15);
                  ('c', 'd', 11);
                  ('c', 'f', 2);
                  ('d', 'e', 6);
                  ('e', 'f', 9)] }

let () = 
    Printf.printf "Vertices of the graph\n";
    let vertices = list_vertices g in 
    List.iter (Printf.printf "%c ") vertices

let () = 
    Printf.printf "Neighbor of vertices: \n";
    let neighbs =  neighbors g 'a' in
    List.iter (fun (v, d) -> Printf.printf "(%c, %d) " v d) neighbs 

let add x y = x + y

let () = 
    Printf.printf "\nShortest path: ";
    let p = dijkstra max_int 0 (+) g 'a' 'e' in
    let path_strings = List.map (String.make 1) p in
    print_endline (String.concat " -> " path_strings)
let gmooh = "
.........00000.........
......00003130000......
....000321322221000....
...00231222432132200...
..0041433223233211100..
..0232231612142618530..
.003152122326114121200.
.031252235216111132210.
.022211246332311115210.
00113232262121317213200
03152118212313211411110
03231234121132221411410
03513213411311414112320
00427534125412213211400
.013322444412122123210.
.015132331312411123120.
.003333612214233913300.
..0219126511415312570..
..0021321524341325100..
...00211415413523200...
....000122111322000....
......00001120000......
.........00000........."

let split_string text delimiter =
  let lines = ref [] in
  let current_line = ref "" in
  String.iter (fun c ->
    if c = delimiter then (
      lines := !current_line :: !lines;
      current_line := ""
    ) else
      current_line := !current_line ^ String.make 1 c
  ) text;
  if !current_line <> "" then
    lines := !current_line :: !lines;
  List.rev !lines

let () =
  let lines = split_string gmooh '\n' in
  List.iter print_endline lines
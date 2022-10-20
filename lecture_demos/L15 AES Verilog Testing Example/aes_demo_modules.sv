/////////////////////////////////////////////
// add_round_key
//  Module which adds the round key to the state
/////////////////////////////////////////////


module add_round_key (
  input   logic [7:0]   state_in  [3:0][3:0],
  input   logic [127:0] w,
  output  logic [7:0]   state_out [3:0][3:0]);

  // TODO: add logic to perform the AddRoundKey tranformation

endmodule

/////////////////////////////////////////////
// add_round_key
//  Module which adds the round key to the state
/////////////////////////////////////////////


module shift_rows (
  input   logic [7:0]   state_in  [3:0][3:0],
  output  logic [7:0]   state_out [3:0][3:0]);

  // TODO: add logic to perform the ShiftRows transformation

endmodule
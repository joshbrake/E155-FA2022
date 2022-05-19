/*
	Lab 1 Code
	
	Josh Brake
  jbrake@hmc.edu
  5/13/22
  
	Pin assignments:

*/

`include "seven_segment_led.sv"

module top (
  input  logic [3:0] s,
  output logic [7:0] led,
  output logic [6:0] seg
);

  logic clk;

  HSOSC hf_osc (.CLKHFEN(1'b1), .CLKHFPU(1'b1), .CLKHF(clk));

  seven_segment_led ssl (~s, seg);

  logic [24:0] clk_divide;

  assign led[7] = clk_divide[24];

  assign led[4] = ~s[2];
  assign led[5] = s[2];

  assign led[0] = ~s[0];
  assign led[1] = s[0];

  assign led[2] = ~s[1];
  assign led[3] = s[1];

  assign led[6] = (~s[3]) & (~s[2]);


	// Clock divider
  always @(posedge clk) 
  begin
    clk_divide <= clk_divide + 1;
  end					
endmodule
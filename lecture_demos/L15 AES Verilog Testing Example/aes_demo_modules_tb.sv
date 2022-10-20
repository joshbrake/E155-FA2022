/////////////////////////////////////////////
// add_round_key_tb
//  Module to test add_round_key module
/////////////////////////////////////////////

module add_round_key_tb();

    // Declare signals
    logic [127:0] key, plaintext, expected;
    // TODO: Declare additional signals: state_in, state_in_1d, state_out, state_out_1d, w
    
    // Initialize inputs
    initial begin   
      // Test case from FIPS-197 Appendix A.1, B
      key       <= 128'h2B7E151628AED2A6ABF7158809CF4F3C;
      plaintext <= 128'h3243F6A8885A308D313198A2E0370734;
      expected  <= 128'h3925841D02DC09FBDC118597196A0B32;
    end
    
    // Instantiate device under test
    add_round_key dut(.state_in(state_in), .w(w), .state_out(state_out));
    
    // Assign state_in from 1d to 2d
    // TODO: write assign statements to assign state_in from 1d to 2d

    // Assign state_out from 2d to 1d
    // TODO: write assign statements to assign state_in from 1d to 2d

    // Logic signal for roundkey from Appendix B
    logic [127:0] roundkey;
    assign roundkey = 128'h193de3bea0f4e22b9ac68d2ae9f84808;
    
    // Apply signals to module and check
    initial begin 
      // Delay and then apply inputs
      #10;
      w <= key;
      state_in_1d <= plaintext;

      // Check outputs
      #10;
      if (state_out_1d == roundkey)
        $display("Test passed!");
      else
        $display("Test failed!");
    end

endmodule


/////////////////////////////////////////////
// shift_rows_tb
//  Module to test shift_rows module
/////////////////////////////////////////////

module shift_rows_tb();

  // TODO:
  // 1. Declare signals
  // 2. Initialize inputs
  // 3. Instantiate device under test
  // 4. Delay and apply inputs
  // 5. Delay and check outputs

endmodule
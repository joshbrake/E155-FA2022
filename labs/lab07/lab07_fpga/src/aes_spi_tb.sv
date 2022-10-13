`timescale 10ns/1ns
/////////////////////////////////////////////
// testbench_aes_spi
// Tests AES with cases from FIPS-197 appendix
// Simulates full system with SPI load
/////////////////////////////////////////////

module testbench_aes_spi();
    logic clk, load, done, sck, sdi, sdo;
    logic [127:0] key, plaintext, cyphertext, expected;
	 logic [255:0] comb;
    logic [8:0] i;

    // Added delay
    logic delay;
    
    // device under test
    aes dut(clk, sck, sdi, sdo, load, done);
    
    // test case
    initial begin   
// Test case from FIPS-197 Appendix A.1, B
        key       <= 128'h2B7E151628AED2A6ABF7158809CF4F3C;
        plaintext <= 128'h3243F6A8885A308D313198A2E0370734;
        expected  <= 128'h3925841D02DC09FBDC118597196A0B32;

// Alternate test case from Appendix C.1
//      key       <= 128'h000102030405060708090A0B0C0D0E0F;
//      plaintext <= 128'h00112233445566778899AABBCCDDEEFF;
//      expected  <= 128'h69C4E0D86A7B0430D8CDB78070B4C55A;
    end
    
    // generate clock and load signals
    initial 
        forever begin
            clk = 1'b0; #5;
            clk = 1'b1; #5;
        end
        
    initial begin
      i = 0;
      load = 1'b1;
      // set delay to true
      delay = 1;
    end

    
	assign comb = {plaintext, key};
    // shift in test vectors, wait until done, and shift out result
    always @(posedge clk) begin
      if (i == 256) load = 1'b0;
      if (i<256) begin
        #1; sdi = comb[255-i];
        #1; sck = 1; #5; sck = 0;
        i = i + 1;
      end else if (done && delay) begin
        #100; // Delay to make sure that the answer is held correctly on the cyphertext before shifting out
        delay = 0;
      end else if (done && i < 384) begin
        #1; sck = 1; 
        #1; cyphertext[383-i] = sdo;
        #4; sck = 0;
        i = i + 1;
      end else if (i == 384) begin
            if (cyphertext == expected)
                $display("Testbench ran successfully");
            else $display("Error: cyphertext = %h, expected %h",
                cyphertext, expected);
            $stop();
      
      end
    end
    
endmodule
# L15 AES Verilog Testing Examples

This folder contains code snippets to demonstrate how to develop simple modules and associated testbenches for the AES cipher.
In particular, the focus here is on two modules which are described in the cipher.
  - `add_round_key` which performs the `AddRoundKey()` transformation 
  - `shift_rows` which performs the `ShiftRows()` 

In addition to the two modules which are left with blanks for you to complete, there are associated testbenches that can be used to individually test the modules.

These files are most easily tested in an independent ModelSim project created separate from the Radiant project used for synthesis.
// filter.s
// E155 Assembly Demo
// Josh Brake (jbrake@hmc.edu)
// Low pass filter by taking four-sample running average
//
// Algorithm
// i: R0, j: R1, sum: R2, a: R3, size: R4
//
// size = 10
// for (i=0; i<size-4; i++) {
//   sum = 0;
//   for (j=0; j<4; j++)
//       sum += a[i+j];
//   a[i] = sum / 4;
// } 

// Directives 
.syntax unified // Specify the syntax for the file
.cpu cortex-m4  // Target CPU is Cortex-M4
.fpu softvfp    // Use software libraries for floating-point operations
.thumb          // Instructions should be encoded as Thumb instructions
            
// Define main globally for other files to call
.global main

// Create test array of bytes. Change this for different test cases.
// This will get loaded to the RAM by the startup code
.data
src:
    .int 42, 54, 60, 72, 78, 86, 100, 112, 124, 130
.size src, .-src
        
dst:
    .fill 128, 4, 0
.size dst, .-dst
    
.text
// The main function
.type main, %function
main:
    ldr r3, =src // load base address of src into R3
    ldr r6, =dst // load base address of dst into R6
    mov r4, #6 // compute size - 4 for comparison
    mov r0, #0 // i = 0
loop_i:
    cmp r0, r4 // i < size -4
    bge done_i // no: finish for i loop
    mov r2, #0 // sum = 0
    mov r1, #0 // j = 0
loop_j:
    cmp r1, #4 // j < 4?
    bge done_j // no: finish for j loop
    add r5, r0, r1 // i + j
    ldr r5, [r3, r5, lsl #2] // a[i+j]
    add r2, r2, r5 // sum += a[i+j]
    add r1, r1, #1 // j++
    b loop_j // end of j loop
done_j:
    asr r5, r2, #2 // sum /4
    // STR R5, [R6, R0] // valid if data stored as bytes
    str r5, [r6, r0, lsl #2] // a[i] = sum/4 (note lsl for word addressing)
    add r0, r0, #1 // i++
    b loop_i // end of i loop
done_i:
    bx LR // return from main
.size main, .-main

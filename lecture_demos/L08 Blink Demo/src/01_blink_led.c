// 01_blink_led.c
// Simple GPIO blink LED with direct pointer manipulation
// Josh Brake
// jbrake@hmc.edu
// 9/26/22

// Pointer for register to turn on clock for GPIO

// Pointers for registers to configure GPIO (see MCU reference manual)
/* TODO: YOUR CODE HERE */

// Complete define statements for the LED pin and delay duration
#define LED_PIN         /* TODO: YOUR CODE HERE */
#define DELAY_DURATION  500

// Simple delay function to use a bunch of NOPs to stall the processor
void delay(int cycles) {
   while (cycles-- > 0) {
      volatile int x=200;
      while (x-- > 0)
         __asm("nop");
   }
}

int main(void) {
    // Turn on clock to GPIO
    /* TODO: YOUR CODE HERE */

    // Set LED_PIN as output
    /* TODO: YOUR CODE HERE */

    // Blink LED
    while(1) {
        delay(DELAY_DURATION);
        
        // Code to toggle the LED each iteration (i.e., set from high to low
        // or from low to high)
        
        /* TODO: YOUR CODE HERE */
    }
    return 0;
}
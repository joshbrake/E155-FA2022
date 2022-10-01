// 01_blink_led.c
// Simple GPIO blink LED with direct pointer manipulation
// Josh Brake
// jbrake@hmc.edu
// 9/26/22

// Pointer for register to turn on clock for GPIOB
volatile unsigned long * RCC_AHB2ENR  = (unsigned long *) (0x4002104CUL);
/* Pointers for registers to configure GPIOB (see chapter 8 of the STM32F401RE
   reference manual starting on p. 146)
*/
volatile unsigned long * GPIOB_BASE   = (unsigned long *) (0x48000400UL); // Base register
volatile unsigned long * GPIOB_MODER  = (unsigned long *) (0x48000400UL); // Mode register
volatile unsigned long * GPIOB_ODR    = (unsigned long *) (0x48000414UL); // Output data register

// Complete define statements for the LED pin and delay duration
#define LED_PIN         3   
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
    // Turn on clock to GPIOB
    *RCC_AHB2ENR |= (1 << 1);

    // Set LED_PIN as output
    *GPIOB_MODER |= (1 << 2*LED_PIN);
    *GPIOB_MODER &= ~(1 << (2*LED_PIN+1));

    // Blink LED
    while(1) {
        delay(DELAY_DURATION);
        // Code to toggle the LED each iteration (i.e., set from high to low
        // or from low to high)
        *GPIOB_ODR ^= (1 << LED_PIN);
    }
    return 0;
}
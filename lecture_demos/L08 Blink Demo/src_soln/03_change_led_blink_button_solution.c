// 03_change_led_blink_button.c
// Change LED blink frequency
// Josh Brake
// jbrake@hmc.edu
// 9/22/21

// Include integer types with specified widths like uint32_t
#include <stdint.h>

// Pointer to AHB2 enable register for turning on GPIOB
volatile unsigned long * RCC_AHB2ENR  = (unsigned long *) (0x4002104CUL);

// Base addresses for GPIO ports
#define GPIOA_BASE (0x48000000UL)
#define GPIOB_BASE (0x48000400UL)

// GPIO register structs here
typedef struct {
  volatile uint32_t MODER;   // GPIO Offset 0x00 GPIO port mode register
  volatile uint32_t OTYPER;  // GPIO Offset 0x04
  volatile uint32_t OSPEEDR; // GPIO Offset 0x08
  volatile uint32_t PURPDR;  // GPIO Offset 0x0C
  volatile uint32_t IDR;     // GPIO Offset 0x10
  volatile uint32_t ODR;     // GPIO Offset 0x14
  volatile uint32_t BSRR;    // GPIO Offset 0x18
  volatile uint32_t LCKR;    // GPIO Offset 0x1C
  volatile uint32_t AFRL;    // GPIO Offset 0x20
  volatile uint32_t AFRH;    // GPIO Offset 0x24
} GPIO;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define GPIOA ((GPIO *) GPIOA_BASE)
#define GPIOB ((GPIO *) GPIOB_BASE)

#define LED_PIN     3             // PB3
#define BUTTON_PIN  2             // PA2
#define DELAY_DURATION_1    100
#define DELAY_DURATION_2    500

void delay(int cycles) {
   while (cycles-- > 0) {
      volatile int x=200;
      while (x-- > 0)
         __asm("nop");
   }
}


int main(void) {
    // Turn on clock to GPIOB and GPIOA
    *RCC_AHB2ENR |= (1 << 1) | (1 << 0);

    // Set LED_PIN as output
    GPIOB->MODER |= (1 << 2*LED_PIN);
    GPIOB->MODER &= ~(1 << (2*LED_PIN+1));
    
    // Set BUTTON_PIN as input
    GPIOA->MODER &= ~(1 << 2*BUTTON_PIN);
    GPIOA->MODER &= ~(1 << (2*BUTTON_PIN+1));
    
    // Configure pull-up register on button input
    GPIOA->PURPDR |= (1 << 2*BUTTON_PIN);
    GPIOA->PURPDR &= ~(1 << (2*BUTTON_PIN+1));
    
    int delay_duration;
    // Blink LED
    while(1) {

      if(!((GPIOA->IDR >> BUTTON_PIN) & 1)) delay_duration = DELAY_DURATION_1;
      else  delay_duration = DELAY_DURATION_2;

      
      delay(delay_duration);
      GPIOB->ODR |= (1 << LED_PIN);
      delay(delay_duration);
      GPIOB->ODR &= ~(1 << LED_PIN);
    }

}
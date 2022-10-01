// main_blink.c
// GPIO blink LED with clock configuration
// Josh Brake
// jbrake@hmc.edu
// 9/28/21

#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"

#define LED_PIN           3
#define DELAY_DURATION    500

void delay(int ms) {
   while (ms-- > 0) {
      volatile int x=1000;
      while (x-- > 0)
         __asm("nop");
   }
}

int main(void) {
  // Configure flash to increase the number of wait states to avoid flash read problems
  configureFlash();

  // Call configureClock() (declared in STM32L432KC_RCC.h)
  configureClock();

  // Turn on clock to GPIOB
  RCC->AHB2ENR |= (1 << 1);

  // Set LED_PIN as output
  pinMode(LED_PIN, GPIO_OUTPUT);

  // Blink LED
  while(1) {
      delay(DELAY_DURATION);
      togglePin(LED_PIN);
  }
  return 0;
}
// main_button_polling_solution.c
// Josh Brake
// jbrake@hmc.edu
// 9/30/20

/*
  This program polls the user button on the Nucleo-F401RE board and has a
  delay within the main loop to simulate the problems with polling for 
  catching events.
*/

#include "main.h"

int main(void) {
    configureFlash();
    configureClock();
    
    // Enable LED as output
    RCC->AHB1ENR.GPIOAEN = 1;
    pinMode(GPIOA, LED_PIN, GPIO_OUTPUT);

    // Enable button as input
    RCC->AHB1ENR.GPIOCEN = 1;
    pinMode(GPIOC, BUTTON_PIN, GPIO_INPUT);

    // Initialize timer
    RCC->APB1ENR |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    uint8_t volatile cur_button_state = digitalRead(GPIOC, BUTTON_PIN);
    uint8_t volatile led_state = 0;
    uint8_t volatile prev_button_state = cur_button_state;

    while(1){
        prev_button_state = cur_button_state;
        cur_button_state = digitalRead(GPIOC, BUTTON_PIN);
        if (prev_button_state == 1 && cur_button_state == 0){
            led_state = !led_state;
            digitalWrite(GPIOA, LED_PIN, led_state);
        }
        delay_millis(DELAY_TIM, 200);
    }
}

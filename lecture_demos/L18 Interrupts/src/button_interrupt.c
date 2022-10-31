// button_interrupt.c
// Josh Brake
// jbrake@hmc.edu
// 10/31/22

#include "main.h"

int main(void) {
    // Enable LED as output
    gpioEnable(GPIO_PORT_A);
    pinMode(LED_PIN, GPIO_OUTPUT);

    // Enable button as input
    gpioEnable(GPIO_PORT_A);
    pinMode(BUTTON_PIN, GPIO_INPUT);

    // Initialize timer
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    initTIM(DELAY_TIM);

    // TODO
    // 1. Enable SYSCFG clock domain in RCC
    // 2. Set EXTICR4 for PC13

    // Enable interrupts globally
    __enable_irq();

    // TODO: Configure interrupt for falling edge of GPIO PC13
    // 1. Configure mask bit
    // 2. Disable rising edge trigger
    // 3. Enable falling edge trigger
    // 4. Turn on EXTI interrupt in NVIC_ISER1

    while(1){   
        delay_millis(TIM2, 200);
    }

}

// TODO: What is the right name for the IRQHandler for PA2?
void XXXXXX(void){
    // Check that the button EXTI_13 was what triggered our interrupt
    if (EXTI->PR & (1 << )){
        // If so, clear the interrupt
        EXTI->PR |= (1 << );

        // Then toggle the LED
        togglePin(LED_PIN);

    }
}

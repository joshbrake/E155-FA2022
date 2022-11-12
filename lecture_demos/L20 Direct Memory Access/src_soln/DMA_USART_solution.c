// DMA_USART_CHAR_main.c
// Josh Brake
// jbrake@hmc.edu
// 11/8/22

// Standard library includes.
#include <stdint.h>
#include <stdlib.h>
// Vendor-provided device header file.
#include "stm32l432xx.h"

#define TIM TIM2
#define USART USART2  // USART2 is the USART instance connected to the virtual COM port on the ST-LINK
// 32-character array

#define MYSTERY_ARRAY

#ifndef MYSTERY_ARRAY
  #define CHAR_ARRAY_SIZE 20
  const char CHAR_ARRAY[CHAR_ARRAY_SIZE] = "This is a DMA Test!\n";
  #define CHAR_PER_SECOND 20
#else
  #define CHAR_ARRAY_SIZE 232
  const char CHAR_ARRAY[CHAR_ARRAY_SIZE] = "\n  __  __  _                    ____        _  \n |  \\/  |(_)  ___  _ __  ___  |  _ \\  ___ | |\n | |\\/| || | / __|| '__|/ _ \\ | |_) |/ __|| |\n | |  | || || (__ | |  | (_) ||  __/ \\__ \\|_|\n |_|  |_||_| \\___||_|   \\___/ |_|    |___/(_)\n";
  #define CHAR_PER_SECOND 100
#endif


#define HSI_FREQ 16000000

/**
 * Main program.
 */
int main(void) {

    ////////////////////////////////
    // RCC Configuration
    ////////////////////////////////

    // Enable peripherals: GPIOA, DMA, TIM2.
    RCC->AHB1ENR  |= (RCC_AHB1ENR_DMA1EN);
    RCC->AHB2ENR  |= (RCC_AHB2ENR_GPIOAEN);
    RCC->APB1ENR1 |= (RCC_APB1ENR1_TIM2EN);
    
    
    ////////////////////////////////
    // USART Configuration
    ////////////////////////////////

    // Set PA2 to ALT function
    GPIOA->MODER &= ~(GPIO_MODER_MODER2);
    GPIOA->MODER |= _VAL2FLD(GPIO_MODER_MODE2, 0b10);
    
    // Clear ALT function settings
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2 | GPIO_AFRL_AFSEL3);
    
    // Configure correct alternate functions (PA2 to AF07, PA15 to AF03)
    GPIOA->AFR[0] |= _VAL2FLD(GPIO_AFRL_AFSEL2,7);
    GPIOA->AFR[1] |= _VAL2FLD(GPIO_AFRH_AFSEL15,3);

    // Configure USART2
    RCC->APB1ENR1 |= (RCC_APB1ENR1_USART2EN); // Set USART2EN
    RCC->CR |= RCC_CR_HSION;  // Turn on HSI 16 MHz clock
    RCC->CCIPR |= _VAL2FLD(RCC_CCIPR_USART2SEL, 2); // Set HSI16 (16 MHz) as USART clock source

    USART->CR1 &= ~(USART_CR1_M); // M=0 corresponds to 8 data bits
    USART->CR2 &= ~(USART_CR2_STOP); // 0b00 corresponds to 1 stop bit
    USART->CR1 &= ~(USART_CR1_OVER8); // Set to 16 times sampling freq

    // Set USART baud rate to 9600

    USART->BRR = (uint16_t) (HSI_FREQ / 9600);
    
    USART->CR1 |= (USART_CR1_UE); // Enable USART
    USART->CR1 |= (USART_CR1_TE | USART_CR1_RE); // Enable USART2


    ////////////////////////////////
    // DMA configuration
    ////////////////////////////////

    // Configure DMA1 to excecute a transaction based on an event from TIM2 update event
    // So, find TIM2_UP which gets muxed into channel 2 of DMA1
    // Need to set C2S[3:0] to 0b0100 to choose TIM2_UP as the DMA trigger

    // DMA1 configuration (channel 2 / selection 4).
    // SxCR register:
    // - Memory-to-peripheral
    // - Circular mode enabled.
    // - Increment memory ptr, don't increment periph ptr.
    // - 8-bit data size for both source and destination.
    // - High priority (2/3).


    // Reset DMA1 Channel 2
    DMA1_Channel2->CCR  &= ~(0xFFFFFFFF);
    DMA1_Channel2->CCR  |= (_VAL2FLD(DMA_CCR_PL,0b10) |
                            _VAL2FLD(DMA_CCR_MINC, 0b1) |
                            _VAL2FLD(DMA_CCR_CIRC, 0b1) |
                            _VAL2FLD(DMA_CCR_DIR, 0b1)
                            );
    
    // Set DMA source and destination addresses.
    // Source: Address of the character array buffer in memory.
    DMA1_Channel2->CMAR = _VAL2FLD(DMA_CMAR_MA, (uint32_t) &CHAR_ARRAY);

    // Dest.: USART data register
    DMA1_Channel2->CPAR = _VAL2FLD(DMA_CPAR_PA, (uint32_t) &(USART->TDR));

    // Set DMA data transfer length (# of samples).
    DMA1_Channel2->CNDTR  |= _VAL2FLD(DMA_CNDTR_NDT, CHAR_ARRAY_SIZE);
    
    // Select 4th option for mux to channel 2
    DMA1_CSELR->CSELR |= _VAL2FLD(DMA_CSELR_C2S, 4);

    // Enable DMA1 channel.
    DMA1_Channel2->CCR  |= DMA_CCR_EN;

    ////////////////////////////////
    // TIM2 Configuration
    ////////////////////////////////

    // Set prescaler and autoreload to issue DMA request at 10 Hz
    TIM->PSC  =  0x0000;
    TIM->ARR  =  SystemCoreClock/CHAR_PER_SECOND;
    
    // Enable trigger output on timer update events.
    TIM->CR2 |= (TIM_CR2_CCDS); // Set DMA request when update event occurs
    
    // Setup DMA request on update event for timer
    TIM->DIER |= (TIM_DIER_UDE);

    // Start the timer.
    TIM->CR1 |=  (TIM_CR1_CEN);

    while (1) {
    }
}
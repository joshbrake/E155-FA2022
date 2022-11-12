// DMA_USART_demo.c
// Josh Brake
// jbrake@hmc.edu
// 11/10/22

// Standard library includes.
#include <stdint.h>
#include <stdlib.h>
// Vendor-provided device header file.
#include "stm32l432xx.h"

#define TIM TIM2
#define USART USART2  // USART2 is the USART instance connected to the virtual COM port on the ST-LINK
// 32-character array

//#define MYSTERY_ARRAY

#ifndef MYSTERY_ARRAY
  #define CHAR_ARRAY_SIZE 20
  const char CHAR_ARRAY[CHAR_ARRAY_SIZE] = "This is a DMA Test!\n";
  #define CHAR_PER_SECOND 10
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

    // TODO: Reset DMA channel configuration
    
    // TODO: Set DMA Channel configuration
    
    // Set DMA source and destination addresses.
    // TODO: Source: Address of the character array buffer in memory.
    

    // TODO: Dest.: USART data register
    

    // TODO: Set DMA data transfer length (# of samples).
    
    
    // TODO: Select correct selection for DMA channel
    

    // TODO: Enable DMA channel.
    

    ////////////////////////////////
    // TIM2 Configuration
    ////////////////////////////////
 
    // Set prescaler and autoreload to issue DMA request at 10 Hz
    TIM->PSC  =  0x0000;
    TIM->ARR  =  SystemCoreClock/CHAR_PER_SECOND;
    
    // TODO: Enable trigger output on timer update events.
    
    
    // TODO: Setup DMA request on update event for timer
    

    // TODO: Start the timer.
    

    while (1) {
    }
}
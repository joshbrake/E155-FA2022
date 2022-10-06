/**
    Main Header: Contains general defines and selected portions of CMSIS files
    @file main.h
    @author Josh Brake
    @version 1.0 10/7/2020
*/

#ifndef MAIN_H
#define MAIN_H

#include "STM32L432KC.h"

// Request defines
#define REQ_UNKNOWN 0
#define REQ_LED_ON 1
#define REQ_LED_OFF 2

// LED pin
#define LED_PIN PA5

#define ESP_USART_ID USART1_ID
#define TERM_USART_ID USART2_ID
#define DELAY_TIM TIM2
#define CMD_DELAY_MS 10
#define BUFFER_SIZE 2048

#endif // MAIN_H
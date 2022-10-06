# Starter Code for Lab 6
The starter code for Lab 6 includes a set of libraries which use the Common Microcontroller Software Interface Standard (CMSIS).
In this lab you are required to use the CMSIS device drivers (mainly the definitions and types in `stm32l432xx.h`).
Beware that these names may clash with code you have used in prior labs, so CMSIS versions of the drivers are provided for you for other peripherals we have used like GPIO and RCC.

The main goal of this lab is to learn about SPI and to write your own device driver using the CMSIS device drivers.
You will need to write a device driver for the SPI peripheral on the MCU and a library to interface with the DS1722 SPI temperature sensor and are provided with a few templates to get you started.
* A barebones SPI device driver (STM32L432KC_SPI.h/.c) with suggested function prototypes (feel free to change or add your own!)
* Blank DS1722.h/.c files in which to write your device driver for the temperature sensor chip.

The starter code sets up a UART and connects to an ESP8266 module running the webserver code to displays a simple web page with buttons which enable you to turn on and off the on-board LED.
Before you start modifying the code to add your SPI functionality, make sure to run the provided starter code to make sure the ESP8266 web server is correctly interfacing with your MCU.

# Hints
* You may want to take some time to look through the provided drivers for other peripherals to get a sense of how to use the CMSIS macros and templates.
In particular, learning how to use `_VAL2FLD` and `_FLD2VAL` can be very helpful.
* Sometimes the ESP8266 and MCU get out of sync and you will get an error when trying to refresh the webpage and connect. Normally an MCU reset (no need to reset the ESP8266) takes care of this issue. The on-board MCU_reset button enables you to conveniently reset the MCU.
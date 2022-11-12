# L20 Direct Memory Access (DMA) Demo

This folder contains code snippets to demonstrate how to use direct memory access on the STM32L432KC.

Scaffolded code with blanks and TODOs is provided to guide you on developing the solution.
The worksheet lists the key registers and configuration options needed to set up the solution.

In this example, DMA is used to transfer data from a character array to the USART data register to send data over a serial connection to the attached host computer at 9600 baud.
The DMA transactions are triggered by update events from a timer running at 10 Hz.

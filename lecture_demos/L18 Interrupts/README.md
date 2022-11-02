# L18 Interrupts Demo

This folder contains code snippets to demonstrate how to use interrupts on the STM32L432KC.

Complete source code and libraries are provided for a polling-based solution.
Scaffolded code with blanks and TODOs is provided to guide you on developing an interrupt-based solution.

The following questions provide a basis for gathering the information required to complete the missing information in `button_interrupt.c`.

## STM32L432KC Interrupt Worksheet
Use the reference manual and datasheet for the MCU to answer the following questions.

1. What bit (register name, address, and bit index) needs to be enabled to turn on the clock domain for accessing the system configuration registers (SYSCFGEN)?
2. What GPIO is configured for the button? What register within the SYSCFG register needs to be configured to enable interrupts from this pin?
3. What is the assembly instruction used to globally enable interrupts? Can this instruction be replaced by a memory-mapped load/store operation?
4. What registers in EXTI need to be configured to trigger interrupts on the falling edge of the button?
5. What is the base address for the EXTI registers?
6. What register needs to be configured in the Nested Vector Interrupt Controller to enable the interrupt? 
7. What is the name of the interrupt handler for IRQHandler for the button GPIO pin? It is defined as <x>_IRQHandler where <x> is the name of the acronym in the vector table. (Hint: The vector table for the MCU is listed in the RM in the chapter on the Nested Vector Interrupt Controller (NVIC). The vector table is also defined in the CMSIS files in the IRQn_Type data type.)
8. Inside the interrupt handler, what registers do we need to check to see if there is an interrupt pending? How do we reset it to clear the pending status?


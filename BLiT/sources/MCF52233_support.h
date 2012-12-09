/*
 * File:        mcf52233_support.h
 * Purpose:     Implements UART basic support, Derivative Specific Interrupt handler and need function needed 
 *              for MSL Support (printf\cout to terminal), defined in <UART.h>
 *
 * Notes:       
 *              
 */

#ifndef __MCF52233_SUPPORT_H__
#define __MCF52233_SUPPORT_H__


#ifdef __cplusplus
extern "C" {
#endif

#if UART_SUPPORT==1 

/********************************************************************/
/*
 * Initialize the UART for 8N1 operation, interrupts disabled, and
 * no hardware flow-control
 *
 * Parameters:
 *  uartch      UART channel to initialize
 *  sysclk      UART System Clock (used to calculate baud)
 *  baud        UART baud rate
 *  settings    Initialization parameters
 */
void uart_init (int uartch, int sysclk, int baud, int settings);

/********************************************************************/
/*
 * Wait for a character to be received on the specified UART
 *
 * Return Values:
 *  the received character
 */
unsigned char uart_getchar (int channel);

/********************************************************************/
/*
 * Wait for space in the UART Tx FIFO and then send a character
 */ 
void uart_putchar (int channel, char ch);

/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */

/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present (int channel);

#endif

/********************************************************************/
/*
 * Derivative Specific Interrupt Handler
 * This is the exception handler for derivative specific exceptions. 
 *
 * Called by mcf5xxx_exception_handler which is called by asm_exception_handler 
 * Functions provided by processor specific C file.
 *
 */
void derivative_handle_interrupt (int vector);


#ifdef __cplusplus
}
#endif

#endif /* __MCF52233_SUPPORT_H__ */

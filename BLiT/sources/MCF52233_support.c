/*
 * File:        mcf52233_support.h
 * Purpose:     Implements UART basic support, Derivative Specific Interrupt handler and need function needed 
 *              for MSL Support (printf\cout to terminal), defined in <UART.h>
 *
 * Notes:       
 *              
 */
#include "support_common.h"
#include "mcf52233_support.h"
#include <stdio.h>

/********************************************************************/
/** Interrupt Handling                                             **/
/********************************************************************/

/********************************************************************/
/*
 * Derivative Specific Interrupt Handler
 * This is the exception handler for derivative specific exceptions. 
 *
 * Called by mcf5xxx_exception_handler which is called by asm_exception_handler 
 * Functions provided by processor specific C file.
 *
 */
void
derivative_handle_interrupt (int vector)
{
    if (vector < 64 || vector > 192) 
    {
		printf("User Defined Vector #%d\n",vector);
    	
    }
}

/********************************************************************/
/** UART Sample Code                                               **/
/********************************************************************/
#if UART_SUPPORT==1 

/********************************************************************/
/*
 * Initialize the UART for 8N1 operation, interrupts disabled, and
 * no hardware flow-control
 *
 * Parameters:
 *  uartch      UART channel to initialize
 *  sysclk      UART System Clock (khz, used to calculate baud)
 *  baud        UART baud rate
 *  settings    Initialization parameters
 */
void uart_init(int /*uartch*/, int sysclk, int baud, int /*settings*/) {
	/*
	 * Initialize all three UARTs for serial communications
	 */

	register uint16 ubgs;

	/*
	 * Set Port UA to initialize URXD0/UTXD0
	 */
    MCF_GPIO_PUAPAR = 0
        | MCF_GPIO_PUAPAR_URXD0_URXD0
        | MCF_GPIO_PUAPAR_UTXD0_UTXD0;

    MCF_GPIO_PUBPAR = 0
        | MCF_GPIO_PUBPAR_URXD1_URXD1
        | MCF_GPIO_PUBPAR_UTXD1_UTXD1;

    MCF_GPIO_PUCPAR = 0
        | MCF_GPIO_PUCPAR_URXD2_URXD2
        | MCF_GPIO_PUCPAR_UTXD2_UTXD2;

	/*
	 * Reset Transmitter
	 */
	MCF_UART0_UCR = MCF_UART_UCR_RESET_TX;
	MCF_UART1_UCR = MCF_UART_UCR_RESET_TX;
	MCF_UART2_UCR = MCF_UART_UCR_RESET_TX;

	/*
	 * Reset Receiver
	 */
	MCF_UART0_UCR = MCF_UART_UCR_RESET_RX;
	MCF_UART1_UCR = MCF_UART_UCR_RESET_RX;
	MCF_UART2_UCR = MCF_UART_UCR_RESET_RX;

	/*
	 * Reset Mode Register
	 */
	MCF_UART0_UCR = MCF_UART_UCR_RESET_MR;
	MCF_UART1_UCR = MCF_UART_UCR_RESET_MR;
	MCF_UART2_UCR = MCF_UART_UCR_RESET_MR;

	/*
	 * No parity, 8-bits per character
	 */
	MCF_UART0_UMR1 = (0
		| MCF_UART_UMR_PM_NONE
		| MCF_UART_UMR_BC_8 );
	MCF_UART1_UMR1 = (0
		| MCF_UART_UMR_PM_NONE
		| MCF_UART_UMR_BC_8 );
	MCF_UART2_UMR1 = (0
		| MCF_UART_UMR_PM_NONE
		| MCF_UART_UMR_BC_8 );

	/*
	 * No echo or loopback, 1 stop bit
	 */
	MCF_UART0_UMR1 = (0
		| MCF_UART_UMR_CM_NORMAL
		| MCF_UART_UMR_SB_STOP_BITS_1);
	MCF_UART1_UMR1 = (0
		| MCF_UART_UMR_CM_NORMAL
		| MCF_UART_UMR_SB_STOP_BITS_1);
	MCF_UART2_UMR1 = (0
		| MCF_UART_UMR_CM_NORMAL
		| MCF_UART_UMR_SB_STOP_BITS_1);

	/*
	 * Set Rx and Tx baud by SYSTEM CLOCK
	 */
	MCF_UART0_UCSR = (0
		| MCF_UART_UCSR_RCS_SYS_CLK
		| MCF_UART_UCSR_TCS_SYS_CLK);
	MCF_UART1_UCSR = (0
		| MCF_UART_UCSR_RCS_SYS_CLK
		| MCF_UART_UCSR_TCS_SYS_CLK);
	MCF_UART2_UCSR = (0
		| MCF_UART_UCSR_RCS_SYS_CLK
		| MCF_UART_UCSR_TCS_SYS_CLK);

	/*
	 * Mask all UART interrupts
	 */
	MCF_UART0_UIMR = 0;
	MCF_UART1_UIMR = 0;
	MCF_UART2_UIMR = 0;

	/*
	 * Calculate baud settings
	 */
	ubgs = (uint16)((sysclk*1000)/(baud * 32));

	MCF_UART0_UBG1 = (uint8)((ubgs & 0xFF00) >> 8);
	MCF_UART0_UBG2 = (uint8)(ubgs & 0x00FF);
	MCF_UART1_UBG1 = (uint8)((ubgs & 0xFF00) >> 8);
	MCF_UART1_UBG2 = (uint8)(ubgs & 0x00FF);
	MCF_UART2_UBG1 = (uint8)((ubgs & 0xFF00) >> 8);
	MCF_UART2_UBG2 = (uint8)(ubgs & 0x00FF);

	/*
	 * Enable receiver and transmitter
	 */
	MCF_UART0_UCR = (0
		| MCF_UART_UCR_TX_ENABLED
		| MCF_UART_UCR_RX_ENABLED);
	MCF_UART1_UCR = (0
		| MCF_UART_UCR_TX_ENABLED
		| MCF_UART_UCR_RX_ENABLED);
	MCF_UART2_UCR = (0
		| MCF_UART_UCR_TX_ENABLED
		| MCF_UART_UCR_RX_ENABLED);

}

/********************************************************************/
/*
 * Wait for a character to be received on the specified UART
 *
 * Return Values:
 *  the received character
 */
unsigned char uart_getchar (int channel)
{
    /* Wait until character has been received */
    while (!(MCF_UART_USR(channel) & MCF_UART_USR_RXRDY))
        ; 
    return MCF_UART_URB(channel);
}
/********************************************************************/
/*
 * Wait for space in the UART Tx FIFO and then send a character
 */ 
void uart_putchar (int channel, char ch)
{
    /* Wait until space is available in the FIFO */
    while (!(MCF_UART_USR(channel) & MCF_UART_USR_TXRDY))
        ;
    /* Send the character */
    MCF_UART_UTB(channel) = (uint8)ch;
}
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present (int channel)
{
    return (MCF_UART_USR(channel) & MCF_UART_USR_RXRDY);
}
#endif

/********************************************************************/


/********************************************************************/
/** <UART.h> Neeeded functions                                     **/
/********************************************************************/

/****************************************************************************/
/*
 * Implementation for CodeWarror MSL interface to serial device (UART.h). 
 * Needed for printf, etc...
 * Only InitializeUART, ReadUARTN, and WriteUARTN are implemented.
 *
 */

/****************************************************************************/
/*
	ReadUARTN
	
	Read N bytes from the UART.
	
	bytes			pointer to result buffer
	limit			size of buffer and # of bytes to read
*/
/****************************************************************************/

UARTError InitializeUART(UARTBaudRate /*baudRate*/)
{
#if UART_SUPPORT==1 
    // UART is initialized in SYSTEM_SysInit to achieve 115200 bauds 
#endif  
	return kUARTNoError;
}

/****************************************************************************/
/*
	ReadUARTN
	
	Read N bytes from the UART.
	
	bytes			pointer to result buffer
	limit			size of buffer and # of bytes to read
*/
/****************************************************************************/
UARTError ReadUARTN(void* bytes, unsigned long limit)
{
	int count;
	UARTError err= kUARTNoError; 
#if UART_SUPPORT==1 
	for (count = 0; count < limit; count++) {
    *( (unsigned char *)bytes + count )=uart_getchar(0);
  }
#endif  
	return err;
}

/****************************************************************************/
UARTError WriteUARTN(const void* bytes, unsigned long length)
{
	int count;
	UARTError err= kUARTNoError; 
#if UART_SUPPORT==1 
	for (count = 0; count < length; count++) {
		uart_putchar(0, *( ((char *)bytes) + count));
	}
#endif	
	return kUARTNoError;
}





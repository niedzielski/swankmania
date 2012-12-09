/*
 * File:		m52233demo_board.h
 * Purpose:		Evaluation board definitions
 *
 * Notes:
 */

#ifndef _M52233DEMO_H
#define _M52233DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

#if UART_SUPPORT==1 
/*** 
 * System Bus Clock Info 
 */
#define SYSTEM_CLOCK  60000    /* system bus frequency */

/*** 
 * Serial Port Info
 * The baud rate to be : 115200
 * Data bits : 8
 * Parity : None
 * Stop Bits : 1
 * Flow Control : None 
 */
#define TERMINAL_PORT       (0)
#define TERMINAL_BAUD       kBaud115200
#endif 

/*
 * Ethernet Port Info
 */
#define FEC_PHY0            (0x00)


/********************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* _M52233DEMO_H */

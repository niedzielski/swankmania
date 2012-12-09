/*
* File:		support_common.h
 * Purpose:		File to be included by all project files
 *
 * Notes:
 */

#ifndef _SUPPORT_COMMON_H_
#define _SUPPORT_COMMON_H_


#define UART_SUPPORT  0 

/* 
 * Include the derivative header files 
 */
#include "MCF52233.h"

/* 
 * Include the derivative support files 
 */
#include "MCF52233_support.h"

/* 
 * Include the board specific header files 
 */
#include "M52233DEMO_board.h"

/* 
 * Include the generic ColdFire support files 
 */
#include "mcf5xxx.h"

/* 
 * Include the Freescale UART specific header file for printf/cout/scanf support 
 */
#include <ansi_parms.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <UART.h>

#ifdef __cplusplus
}
#endif

/********************************************************************/

#endif /* _SUPPORT_COMMON_H_ */


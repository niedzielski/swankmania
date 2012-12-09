/* Coldfire C Header File
 * Copyright Freescale Semiconductor Inc
 * All rights reserved.
 *
 * 2007/03/19 Revision: 0.91
 */

#ifndef __MCF52233_H__
#define __MCF52233_H__


/********************************************************************/
/*
 * The basic data types
 */

typedef unsigned char           uint8;   /*  8 bits */
typedef unsigned short int      uint16;  /* 16 bits */
typedef unsigned long int       uint32;  /* 32 bits */

typedef signed char             int8;    /*  8 bits */
typedef signed short int        int16;   /* 16 bits */
typedef signed long int         int32;   /* 32 bits */

typedef volatile uint8          vuint8;  /*  8 bits */
typedef volatile uint16         vuint16; /* 16 bits */
typedef volatile uint32         vuint32; /* 32 bits */

#ifdef __cplusplus
extern "C" {
#endif

#pragma define_section system ".system" far_absolute RW

/***
 * MCF52233 Derivative Memory map definitions from linker command files:
 * __IPSBAR, __RAMBAR, __RAMBAR_SIZE, __FLASHBAR, __FLASHBAR_SIZE linker
 * symbols must be defined in the linker command file.
 */

extern __declspec(system)  uint8 __IPSBAR[];
extern __declspec(system)  uint8 __RAMBAR[];
extern __declspec(system)  uint8 __RAMBAR_SIZE[];
extern __declspec(system)  uint8 __FLASHBAR[];
extern __declspec(system)  uint8 __FLASHBAR_SIZE[];

#define IPSBAR_ADDRESS   (uint32)__IPSBAR
#define RAMBAR_ADDRESS   (uint32)__RAMBAR
#define RAMBAR_SIZE      (uint32)__RAMBAR_SIZE
#define FLASHBAR_ADDRESS (uint32)__FLASHBAR
#define FLASHBAR_SIZE    (uint32)__FLASHBAR_SIZE


#include "MCF52233_SCM.h"
#include "MCF52233_DMA.h"
#include "MCF52233_UART.h"
#include "MCF52233_I2C.h"
#include "MCF52233_QSPI.h"
#include "MCF52233_RTC.h"
#include "MCF52233_DTIM.h"
#include "MCF52233_INTC.h"
#include "MCF52233_GIACR.h"
#include "MCF52233_FEC.h"
#include "MCF52233_GPIO.h"
#include "MCF52233_PAD.h"
#include "MCF52233_RCM.h"
#include "MCF52233_PMM.h"
#include "MCF52233_CCM.h"
#include "MCF52233_CLOCK.h"
#include "MCF52233_EPORT.h"
#include "MCF52233_PIT.h"
#include "MCF52233_ADC.h"
#include "MCF52233_GPTA.h"
#include "MCF52233_PWM.h"
#include "MCF52233_CFM.h"
#include "MCF52233_EPHY.h"

#ifdef __cplusplus
}
#endif


#endif /* __MCF52233_H__ */

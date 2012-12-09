/*
 * File:		m52233demo_sysinit.h
 * Purpose:		Power-on Reset configuration of the M52233DEMO.
 *
 * Notes:
 *
 */
 
#ifndef __M52233DEMO_SYSINIT_H__
#define __M52233DEMO_SYSINIT_H__

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************
*	Out of reset, the low-level assembly code calls this 
*	routine to initialize the MCF52233 modules for the  
*	M52233DEMO board. 
********************************************************/
void SYSTEM_SysInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __M52233DEMO_SYSINIT_H__ */



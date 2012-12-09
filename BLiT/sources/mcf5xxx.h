/*
 * File:		mcf5xxx.h
 * Purpose:		Definitions common to all ColdFire processors
 *
 * Notes:
 */

#ifndef _CPU_MCF5XXX_H
#define _CPU_MCF5XXX_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************/
/*
 * Functions provided in mcf5xxx.c
 */
 
/***
 * MCF5xxx startup copy function:
 *
 * Set VBR and performs data initialization.
 * The following symbols should be defined in the lcf:
 * __DATA_ROM
 * __DATA_RAM
 * __DATA_END
 * __BSS_START
 * __BSS_END
 * __VECTOR_RAM
 *
 * VECTOR_TABLE must be defined to the start of the VECTOR_TABLE in the code
 * In case VECTOR_TABLE address is different from __VECTOR_RAM,
 * the vector table is copied from VECTOR_TABLE to __VECTOR_RAM.
 * In any case VBR is set to __VECTOR_RAM.
 */
void mcf5xxx_startup(void);

/********************************************************************
 * MCF5xxx ASM utility functions
 */
/*asm*/ void mcf5xxx_wr_vbr (unsigned long);

/***********************************************************************/
/*
 * This is the exception handler for all defined exceptions.  Most
 * exceptions do nothing, but some of the more important ones are
 * handled to some extent.
 *
 * Called by asm_exception_handler 
 */
void mcf5xxx_exception_handler(void *);


#ifdef __cplusplus
}
#endif

#endif	/* _CPU_MCF5XXX_H */


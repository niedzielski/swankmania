/*
 * File:	mcf5xxx.c
 * Purpose: Generic high-level routines for ColdFire processors
 *
 * Notes:		
 */
#include "support_common.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int __call_static_initializers(void);

#ifdef __cplusplus
}
#endif


/********************************************************************
 * MCF5xxx ASM utility functions
 */
asm void mcf5xxx_wr_vbr(unsigned long) { /* Set VBR */
	move.l	4(SP),D0
    movec d0,VBR 
	nop
	rts	
}	

/********************************************************************
 * MCF5xxx startup copy functions:
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
void mcf5xxx_startup(void)
{
	/*
	 * Memory map definitions from linker command files used by mcf5xxx_startup
	 */
	extern __declspec(system) uint8 __DATA_ROM[];
	extern __declspec(system) uint8 __DATA_RAM[];
	extern __declspec(system) uint8 __DATA_END[];
	extern __declspec(system) uint8 __BSS_START[];
	extern __declspec(system) uint8 __BSS_END[];
	extern __declspec(system) uint32 VECTOR_TABLE[];
	extern __declspec(system) uint32 __VECTOR_RAM[];

	register uint32 n;
	register uint8 *dp, *sp;

	/* 
     * Copy the vector table to RAM 
     */
	if (__VECTOR_RAM != VECTOR_TABLE)
	{
		for (n = 0; n < 256; n++)
			__VECTOR_RAM[n] = VECTOR_TABLE[n];
	}
	mcf5xxx_wr_vbr((uint32)__VECTOR_RAM);

	/* 
	 * Move initialized data from ROM to RAM. 
	 */
	if (__DATA_ROM != __DATA_RAM)
	{
		dp = (uint8 *)__DATA_RAM;
		sp = (uint8 *)__DATA_ROM;
		n = __DATA_END - __DATA_RAM;
		while (n--)
			*dp++ = *sp++;
	}
 
	/* 
	 * Zero uninitialized data 
	 */
	if (__BSS_START != __BSS_END)
	{
		sp = (uint8 *)__BSS_START;
		n = __BSS_END - __BSS_START;
		while (n--)
			*sp++ = 0;
	}

    /*
	 * Initialize static C++ objects
	 */
	__call_static_initializers();
}

/***********************************************************************
 *
 * This is the exception handler for all defined exceptions.  Most
 * exceptions do nothing, but some of the more important ones are
 * handled to some extent.
 *
 * Called by asm_exception_handler 
 *
 * The ColdFire family of processors has a simplified exception stack
 * frame that looks like the following:
 *
 *              3322222222221111 111111
 *              1098765432109876 5432109876543210
 *           8 +----------------+----------------+
 *             |         Program Counter         |
 *           4 +----------------+----------------+
 *             |FS/Fmt/Vector/FS|      SR        |
 *   SP -->  0 +----------------+----------------+
 *
 * The stack self-aligns to a 4-byte boundary at an exception, with
 * the FS/Fmt/Vector/FS field indicating the size of the adjustment
 * (SP += 0,1,2,3 bytes).
 */
#define MCF5XXX_RD_SF_FORMAT(PTR)	\
	((*((uint16 *)(PTR)) >> 12) & 0x00FF)

#define MCF5XXX_RD_SF_VECTOR(PTR)	\
	((*((uint16 *)(PTR)) >>  2) & 0x00FF)

#define MCF5XXX_RD_SF_FS(PTR)		\
	( ((*((uint16 *)(PTR)) & 0x0C00) >> 8) | (*((uint16 *)(PTR)) & 0x0003) )

#define MCF5XXX_SF_SR(PTR)	*((uint16 *)(PTR)+1)
#define MCF5XXX_SF_PC(PTR)	*((uint32 *)(PTR)+1)

#define MCF5XXX_EXCEPTFMT  "%s -- PC = %#08X\n"

void mcf5xxx_exception_handler(void *framep) 
{
	switch (MCF5XXX_RD_SF_FORMAT(framep))
	{
		case 4:
		case 5:
		case 6:
		case 7:
			break;
		default:
			printf(MCF5XXX_EXCEPTFMT,"Illegal stack type", MCF5XXX_SF_PC(framep));
			break;
	}

	switch (MCF5XXX_RD_SF_VECTOR(framep))
	{
		case 2:
			printf(MCF5XXX_EXCEPTFMT, "Access Error", MCF5XXX_SF_PC(framep));
			switch (MCF5XXX_RD_SF_FS(framep))
			{
				case 4:
					printf("Error on instruction fetch\n");
					break;
				case 8:
					printf("Error on operand write\n");
					break;
				case 9:
					printf("Attempted write to write-protected space\n");
					break;
				case 12:
					printf("Error on operand read\n");
					break;
				default:
					printf("Reserved Fault Status Encoding\n");
					break;
			}
			break;
		case 3:
			printf(MCF5XXX_EXCEPTFMT, "Address Error", MCF5XXX_SF_PC(framep));
			switch (MCF5XXX_RD_SF_FS(framep))
			{
				case 4:
					printf("Error on instruction fetch\n");
					break;
				case 8:
					printf("Error on operand write\n");
					break;
				case 9:
					printf("Attempted write to write-protected space\n");
					break;
				case 12:
					printf("Error on operand read\n");
					break;
				default:
					printf("Reserved Fault Status Encoding\n");
					break;
			}
			break;
		case 4:
			printf(MCF5XXX_EXCEPTFMT, "Illegal instruction", MCF5XXX_SF_PC(framep));
			break;
		case 8:
			printf(MCF5XXX_EXCEPTFMT, "Privilege violation", MCF5XXX_SF_PC(framep));
			break;
		case 9:
			printf(MCF5XXX_EXCEPTFMT, "Trace Exception", MCF5XXX_SF_PC(framep));
			break;
		case 10:
			printf(MCF5XXX_EXCEPTFMT, "Unimplemented A-Line Instruction", \
				MCF5XXX_SF_PC(framep));
			break;
		case 11:
			printf(MCF5XXX_EXCEPTFMT, "Unimplemented F-Line Instruction", \
				MCF5XXX_SF_PC(framep));
			break;
		case 12:
			printf(MCF5XXX_EXCEPTFMT, "Debug Interrupt", MCF5XXX_SF_PC(framep));
			break;
		case 14:
			printf(MCF5XXX_EXCEPTFMT, "Format Error", MCF5XXX_SF_PC(framep));
			break;
		case 15:
			printf(MCF5XXX_EXCEPTFMT, "Unitialized Interrupt", MCF5XXX_SF_PC(framep));
			break;
		case 24:
			printf(MCF5XXX_EXCEPTFMT, "Spurious Interrupt", MCF5XXX_SF_PC(framep));
			break;
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
			printf("Autovector interrupt level %d\n",
				MCF5XXX_RD_SF_VECTOR(framep) - 24);
			break;
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
			printf("TRAP #%d\n", MCF5XXX_RD_SF_VECTOR(framep) - 32);
			break;
		case 5:
		case 6:
		case 7:
		case 13:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
			printf("Reserved: #%d\n", MCF5XXX_RD_SF_VECTOR(framep));
			break;
		default:
            derivative_handle_interrupt(MCF5XXX_RD_SF_VECTOR(framep));
			break;
	}
}

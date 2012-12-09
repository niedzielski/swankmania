/*
 * File:	mcf5xxx_asmhandler.s
 * Purpose:	asm exception handler for all ColdFire processors.
 *
 * Notes:	
 *
 */

    .extern _mcf5xxx_exception_handler


	.global asm_exception_handler


	.text
	.function "asm_exception_handler",asm_exception_handler,asm_exception_handler_end-asm_exception_handler

/********************************************************************
 * This routine is the lowest-level exception handler.
 */
asm_exception_handler:
            link     a6,#0 
            lea     -20(sp), sp
            movem.l d0-d2/a0-a1, (sp)
            pea.l   20(sp)              /* push exception frame address */
            jsr     _mcf5xxx_exception_handler
            movem.l 4(sp), d0-d2/a0-a1
            lea     24(sp), sp
            unlk a6
            rte
asm_exception_handler_end:
/********************************************************************/
	.end

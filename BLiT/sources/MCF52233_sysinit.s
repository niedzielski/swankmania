/*
 * File:	mcf5223x_sysinit.s
 * Purpose:	Assembly reset function for mcf5223x.
 *
 * Notes:	
 *
 */
 
/***
 * MCF5223x Derivative Memory map definitions from linker command files:
 * __IPSBAR, __RAMBAR, __RAMBAR_SIZE, __FLASHBAR, __FLASHBAR_SIZE linker
 * symbols must be defined in the linker command file.
 */ 
    .extern ___IPSBAR;
    .extern ___RAMBAR;
    .extern	___RAMBAR_SIZE;
    .extern ___FLASHBAR;
    .extern ___FLASHBAR_SIZE;
    .extern ___SP_INIT
/***
 *   void SYSTEM_SysInit(void); : does Power-on Reset configuration of the M5253EVB
 */     
	.extern _SYSTEM_SysInit


/***
 *   int main(void); must be defined and we use mangling
 */     
    .extern _main
    
    .global _asm_startmeup
   
	.text
	.function "_asm_startmeup",_asm_startmeup,_asm_startmeup_end-_asm_startmeup

/********************************************************************
 * 
 * This is the main entry point upon hard reset.  The memory map is
 * setup based on linker file definitions, then the higher level
 * system initialization routine is called.  Finally, we jump to the
 * "main" process. 
 */
_asm_startmeup: 
	move.w	#0x2700,SR
    
	/* Initialize RAMBAR: locate SRAM and validate it */
	move.l	#(___RAMBAR + 0x21),d0
	movec	d0,RAMBAR1
	
	/* Initialize IPSBAR */
	move.l	#___IPSBAR,d0
  add.l   #0x1,d0
	move.l	d0,0x40000000

  /* Initialize FLASHBAR */
  move.l  #___FLASHBAR,d0
  cmp.l   #0x00000000,d0
  bne     change_flashbar
  add.l   #0x61,d0
  movec   d0,FLASHBAR

_continue_startup:    
  /* At this point the memory should be correctly setup */

	/* Locate Stack Pointer */ 
	move.l	#___SP_INIT,sp

	/* Initialize periphs, bus, memory, etc... */
	jsr		_SYSTEM_SysInit
	
	/* Initialize A6 */
	movea.l #0,A6	
	link A6,#0
	
    	
	/* Jump to the main process */
	jsr		_main
	
	nop
	nop
	halt


change_flashbar:
    /* 
     * The following sequence is used to set FLASHBAR. Since we may 
     * be executing from Flash, we must put the routine into SRAM for
     * execution and then jump back to Flash using the new address.
     *
     * The following instructions are coded into the SRAM:
     *
     * move.l	#(___FLASHBAR + 0x61),d0
     * movec	d0, RAMBAR
     * jmp		_continue_startup
     *
     * An arbitrary SRAM address is chosen until the real address
     * can be loaded.
     *
     * This routine is not necessary if the default Flash address
     * (0x00000000) is used.
     *
     * If running in SRAM, change_flashbar should not be executed 
     */

	move.l  #___RAMBAR,a0

	/* Code "move.l #(___FLASHBAR + 0x61),d0" into SRAM */
	move.w  #0x203C,d0
	move.w  d0,(a0)+
	move.l  #___FLASHBAR,d0
  add.l   #0x61,d0
  move.l  d0,(a0)+
	
	/* Code "movec d0,FLASHBAR" into SRAM */
	move.l  #0x4e7b0C04,d0
	move.l  d0,(a0)+
		
	/* Code "jmp _continue_startup" into SRAM */
	move.w  #0x4EF9,d0
	move.w  d0,(a0)+
	move.l  #_continue_startup,d0
	move.l  d0,(a0)+

	/* Jump to code segment in internal SRAM */
	jmp	    ___RAMBAR


_asm_startmeup_end:
/********************************************************************/
	.end
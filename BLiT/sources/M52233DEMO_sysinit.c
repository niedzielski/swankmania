/*
 * File:		m52233demo_sysinit.c
 * Purpose:		Power-on Reset configuration of the M52233DEMO.
 *
 * Notes: 
 *
 */
#include "support_common.h"
#include "m52233demo_sysinit.h"

 /* Cache Control Register */
#define MCF5XXX_CACR_CENB       (0x80000000)
#define MCF5XXX_CACR_DEC        (0x80000000)
#define MCF5XXX_CACR_DW         (0x40000000)
#define MCF5XXX_CACR_DESB       (0x20000000)
#define MCF5XXX_CACR_CPDI       (0x10000000)
#define MCF5XXX_CACR_DDPI       (0x10000000)
#define MCF5XXX_CACR_CPD        (0x10000000)
#define MCF5XXX_CACR_CFRZ       (0x08000000)
#define MCF5XXX_CACR_DHLCK      (0x08000000)
#define MCF5XXX_CACR_DDCM_WT    (0x00000000)
#define MCF5XXX_CACR_DDCM_CB    (0x02000000)
#define MCF5XXX_CACR_DDCM_IP    (0x04000000)
#define MCF5XXX_CACR_DDCM_II    (0x06000000)
#define MCF5XXX_CACR_CINV       (0x01000000)
#define MCF5XXX_CACR_DCINVA     (0x01000000)
#define MCF5XXX_CACR_DIDI       (0x00800000)
#define MCF5XXX_CACR_DDSP       (0x00800000)
#define MCF5XXX_CACR_DISD       (0x00400000)
#define MCF5XXX_CACR_INVI       (0x00200000)
#define MCF5XXX_CACR_INVD       (0x00100000)
#define MCF5XXX_CACR_BEC        (0x00080000)
#define MCF5XXX_CACR_BCINVA     (0x00040000)
#define MCF5XXX_CACR_IEC        (0x00008000)
#define MCF5XXX_CACR_DNFB       (0x00002000)
#define MCF5XXX_CACR_IDPI       (0x00001000)
#define MCF5XXX_CACR_IHLCK      (0x00000800)
#define MCF5XXX_CACR_CEIB       (0x00000400)
#define MCF5XXX_CACR_IDCM       (0x00000400)
#define MCF5XXX_CACR_DCM_WR     (0x00000000)
#define MCF5XXX_CACR_DCM_CB     (0x00000100)
#define MCF5XXX_CACR_DCM_IP     (0x00000200)
#define MCF5XXX_CACR_DCM        (0x00000200)
#define MCF5XXX_CACR_DCM_II     (0x00000300)
#define MCF5XXX_CACR_DBWE       (0x00000100)
#define MCF5XXX_CACR_ICINVA     (0x00000100)
#define MCF5XXX_CACR_IDSP       (0x00000080)
#define MCF5XXX_CACR_DWP        (0x00000020)
#define MCF5XXX_CACR_EUSP       (0x00000020)
#define MCF5XXX_CACR_EUST       (0x00000020)
#define MCF5XXX_CACR_DF         (0x00000010)
#define MCF5XXX_CACR_CLNF_00    (0x00000000)
#define MCF5XXX_CACR_CLNF_01    (0x00000002)
#define MCF5XXX_CACR_CLNF_10    (0x00000004)
#define MCF5XXX_CACR_CLNF_11    (0x00000006)

asm void mcf5xxx_wr_cacr(unsigned long) { /* Set VBR */
    move.l  4(SP),D0
    //.long   0x4e7b0002      /* movec d0,cacr */
    movec d0,cacr 
    nop
    
    rts
}


/********************************************************************/
static void mcf52233_wtm_init(void)
{
	/*
	 * Disable Software Watchdog Timer
	 */
	MCF_SCM_CWCR = 0;
}

/********************************************************************/
static void mcf52233_pll_init(void)
{

//MCF_CLOCK_CCHR =0x05; // The PLL pre divider - 25MHz / 5 = 5MHz 

	/* The PLL pre-divider affects this!!! 
	 * Multiply 25Mhz reference crystal /CCHR by 12 to acheive system clock of 60Mhz
	 */

	MCF_CLOCK_SYNCR = MCF_CLOCK_SYNCR_MFD(4) | MCF_CLOCK_SYNCR_CLKSRC| MCF_CLOCK_SYNCR_PLLMODE | MCF_CLOCK_SYNCR_PLLEN ;

	while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))
	{
	}
}

/********************************************************************/
static void mcf52233_scm_init(void)
{
	/*
	 * Enable on-chip modules to access internal SRAM
	 */
	MCF_SCM_RAMBAR = (0
		| MCF_SCM_RAMBAR_BA(RAMBAR_ADDRESS)
		| MCF_SCM_RAMBAR_BDE);
}

/********************************************************************/
static void mcf52233_gpio_init(void)
{
  uint32 myctr; 		//generic counter variable

	/*
	 * Initialize PLDPAR to enable Ethernet Leds
	 */
  MCF_GPIO_PLDPAR = (0
  
		 | MCF_GPIO_PLDPAR_ACTLED_ACTLED 
		 | MCF_GPIO_PLDPAR_LINKLED_LINKLED 
		 | MCF_GPIO_PLDPAR_SPDLED_SPDLED 
		 | MCF_GPIO_PLDPAR_DUPLED_DUPLED 
		 | MCF_GPIO_PLDPAR_COLLED_COLLED 
		 | MCF_GPIO_PLDPAR_RXLED_RXLED   
		 | MCF_GPIO_PLDPAR_TXLED_TXLED);  

	/*
	 * Initialize Port TA to enable Axcel control
	 */
	MCF_GPIO_PTAPAR = 0x00; 
	MCF_GPIO_DDRTA  = 0x0F;
	MCF_GPIO_PORTTA = 0x04;
			  
  // set phy address to zero
  MCF_EPHY_EPHYCTL1 = MCF_EPHY_EPHYCTL1_PHYADD(FEC_PHY0); //	FEC_PHY0 from m52233evb.h 

  //Enable EPHY module with PHY clocks disabled
  //Do not turn on PHY clocks until both FEC and EPHY are completely setup (see Below)
  MCF_EPHY_EPHYCTL0 = (uint8)(MCF_EPHY_EPHYCTL0_DIS100 | MCF_EPHY_EPHYCTL0_DIS10);
  
  //Enable auto_neg at start-up
  MCF_EPHY_EPHYCTL0 = (uint8)(MCF_EPHY_EPHYCTL0 & (MCF_EPHY_EPHYCTL0_ANDIS));

  //Enable EPHY module
  MCF_EPHY_EPHYCTL0 = (uint8)(MCF_EPHY_EPHYCTL0_EPHYEN | MCF_EPHY_EPHYCTL0);
  //Let PHY PLLs be determined by PHY
  MCF_EPHY_EPHYCTL0 = (uint8)(MCF_EPHY_EPHYCTL0  & ~(MCF_EPHY_EPHYCTL0_DIS100 | MCF_EPHY_EPHYCTL0_DIS10)); 

  //printf("ePHY enabled \n\r");
	
  //DELAY, Delay start-up
  for (myctr=200000; myctr >0; myctr--)
  {
  }
  
  //printf("ePHY Ready \n\r");
}

/********************************************************************/

void SYSTEM_SysInit (void)
{
	/*******************************************************
	*	Out of reset, the low-level assembly code calls this 
	*	routine to initialize the MCF52233 modules for the  
	*	M52233DEMO board. 
	********************************************************/

  /* 
   * Allow interrupts from ABORT, SW1, SW2, and SW3 (IRQ[1,4,7,11]) 
   */
   
  /* Enable IRQ signals on the port */
  MCF_GPIO_PNQPAR = 0
      | MCF_GPIO_PNQPAR_IRQ1_IRQ1
      | MCF_GPIO_PNQPAR_IRQ4_IRQ4
      | MCF_GPIO_PNQPAR_IRQ7_IRQ7;
  
  MCF_GPIO_PGPPAR = 0
      | MCF_GPIO_PGPPAR_IRQ11_IRQ11;
  
  /* Set EPORT to look for rising edges */
  MCF_EPORT0_EPPAR = 0
      | MCF_EPORT_EPPAR_EPPA1_RISING
      | MCF_EPORT_EPPAR_EPPA4_RISING
      | MCF_EPORT_EPPAR_EPPA7_RISING;
      
  MCF_EPORT1_EPPAR = 0
      | MCF_EPORT_EPPAR_EPPA11_RISING;
      
  /* Clear any currently triggered events on the EPORT  */
  MCF_EPORT0_EPIER = 0
      | MCF_EPORT_EPIER_EPIE1
      | MCF_EPORT_EPIER_EPIE4
      | MCF_EPORT_EPIER_EPIE7;
     
  MCF_EPORT1_EPIER = 0
      | MCF_EPORT_EPIER_EPIE11;
     
  /* Enable interrupts in the interrupt controller */
  MCF_INTC0_IMRL &= ~(0
      | MCF_INTC_IMRL_INT_MASK1 
      | MCF_INTC_IMRL_INT_MASK4 
      | MCF_INTC_IMRL_INT_MASK7 
      | MCF_INTC_IMRL_MASKALL);

  MCF_INTC1_IMRH &= ~(0
      | MCF_INTC_IMRH_INT_MASK35);
        
	MCF_INTC1_ICR35 = MCF_INTC_ICR_IL(4);

	MCF_GPIO_PDDPAR = 0x0F;
	
	/* Set real time clock freq */

	MCF_CLOCK_RTCDR = 25000000;

	/* Call MCF5xxx startup copy function */
    mcf5xxx_startup();
	
	mcf52233_wtm_init();
	mcf52233_pll_init();
	mcf52233_scm_init();
#if UART_SUPPORT==1 	
	uart_init(0,SYSTEM_CLOCK, TERMINAL_BAUD, 0);
#endif
	mcf52233_gpio_init();
	
	/* Turn Instruction Cache ON */
	mcf5xxx_wr_cacr(0
		| MCF5XXX_CACR_CENB
		| MCF5XXX_CACR_CINV
		| MCF5XXX_CACR_DISD
		| MCF5XXX_CACR_CEIB
		| MCF5XXX_CACR_CLNF_00);
	
}






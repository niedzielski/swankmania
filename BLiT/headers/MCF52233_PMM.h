/* Coldfire C Header File
 * Copyright Freescale Semiconductor Inc
 * All rights reserved.
 *
 * 2007/03/19 Revision: 0.91
 */

#ifndef __MCF52233_PMM_H__
#define __MCF52233_PMM_H__


/*********************************************************************
*
* Power Management (PMM)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_PMM_LPICR                        (*(vuint8 *)(&__IPSBAR[0x12]))
#define MCF_PMM_LPCR                         (*(vuint8 *)(&__IPSBAR[0x110007]))


/* Bit definitions and macros for MCF_PMM_LPICR */
#define MCF_PMM_LPICR_XLPM_IPL(x)            (((x)&0x7)<<0x4)
#define MCF_PMM_LPICR_ENBSTOP                (0x80)

/* Bit definitions and macros for MCF_PMM_LPCR */
#define MCF_PMM_LPCR_LVDSE                   (0x2)
#define MCF_PMM_LPCR_STPMD(x)                (((x)&0x3)<<0x3)
#define MCF_PMM_LPCR_STPMD_SYS_DISABLED      (0)
#define MCF_PMM_LPCR_STPMD_SYS_CLKOUT_DISABLED (0x8)
#define MCF_PMM_LPCR_STPMD_ONLY_OSC_ENABLED  (0x10)
#define MCF_PMM_LPCR_STPMD_ALL_DISABLED      (0x18)
#define MCF_PMM_LPCR_LPMD(x)                 (((x)&0x3)<<0x6)
#define MCF_PMM_LPCR_LPMD_RUN                (0)
#define MCF_PMM_LPCR_LPMD_DOZE               (0x40)
#define MCF_PMM_LPCR_LPMD_WAIT               (0x80)
#define MCF_PMM_LPCR_LPMD_STOP               (0xC0)


#endif /* __MCF52233_PMM_H__ */

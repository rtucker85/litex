#ifndef __IRQ_H
#define __IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <system.h>
#include <generated/csr.h>
#include <generated/soc.h>

// The CVA6 uses a Platform-Level Interrupt Controller (PLIC) which
// is programmed and queried via a set of MMIO registers.

#define PLIC_BASE    0x0c000000L // Base address and per-pin priority array
#define PLIC_PENDING 0x0c001000L // Bit field matching currently pending pins
#define PLIC_ENABLED 0x0c002000L // Bit field corresponding to the current mask
#define PLIC_THRSHLD 0x0c200000L // Per-pin priority must be >= this to trigger
#define PLIC_CLAIM   0x0c200004L // Claim & completion register address

#define PLIC_EXT_IRQ_BASE 1

static inline unsigned int irq_getie(void)
{
	return (csrr(mstatus) & CSR_MSTATUS_MIE) != 0;
}

static inline void irq_setie(unsigned int ie)
{
	if(ie) csrs(mstatus,CSR_MSTATUS_MIE); else csrc(mstatus,CSR_MSTATUS_MIE);
}

static inline unsigned int irq_getmask(void)
{
	return *((unsigned int *)PLIC_ENABLED) >> 1;
}

static inline void irq_setmask(unsigned int mask)
{
	*((unsigned int *)PLIC_ENABLED) = mask << 1;
}

static inline unsigned int irq_pending(void)
{
	return *((unsigned int *)PLIC_PENDING) >> 1;
}

#ifdef __cplusplus
}
#endif

#endif /* __IRQ_H */

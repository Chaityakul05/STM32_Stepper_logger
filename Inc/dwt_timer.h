/*
 * dwt_timer.h
 *
 *  Created on: Jul 5, 2025
 *      Author: chait
 */

#ifndef DWT_TIMER_H_
#define DWT_TIMER_H_

#include <stdint.h>

/* ---------- Register Base Addresses ---------- */
#define DWT_BASE          (0xE0001000UL)
#define DEMCR_BASE        (0xE000EDFCUL)

/* ---------- Register Definitions ------------- */
#define DWT_CTRL          (*(volatile uint32_t*)(DWT_BASE + 0x00))
#define DWT_CYCCNT        (*(volatile uint32_t*)(DWT_BASE + 0x04))

#define DEMCR             (*(volatile uint32_t*)(DEMCR_BASE))

/* ---------- Bit Definitions ------------------ */
#define DEMCR_TRCENA      (1 << 24)
#define DWT_CTRL_CYCCNTENA (1 << 0)

/* ---------- Clock Config ---------------------- */
#define SYS_FREQ          8000000UL  // Default 8 MHz, adjust if PLL used

/* ---------- Function Prototypes -------------- */
void DWT_Delay_Init(void);
void DWT_Delay_us(uint32_t us);
uint32_t DWT_GetMicroseconds(void);


#endif /* DWT_TIMER_H_ */

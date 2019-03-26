/**
 * @file   tic_toc.c
 *
 * @brief  Implementation of tic-toc routines for interacting with ARM timer
 *
 * @date   Feb.14th, 2018
 * @author David Dong <haochend@andrew.cmu.edu>
 */

#include <tic_toc.h>
#include <BCM2836.h>

/* Register physical addresses */
/** @brief physical address for timer load reg */
#define TIMER_LOAD_REG (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0xb400)
/** @brief physical address for timer value reg */
#define TIMER_VAL_REG (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0xb404)
/** @brief physical address for timer control reg */
#define TIMER_CNTL_REG (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0xb408)

/** @brief Bit mask #1 for control register */
#define CNTL_MASK1 ((1<<7) | 2)
/** @brief Bit mask #2 for control register */
#define CNTL_MASK2 (~(3<<2))

/** @brief Max timer value */
#define TIMER_MAX 0xFFFFFFFF
/**
 * @brief Configures the arm timer to start running from the starting point with the default frequency.
 *        The Timer should run in 32 bit mode, with a prescaler of 1
 */
void tic(void) {
  *TIMER_CNTL_REG |= CNTL_MASK1;
  *TIMER_CNTL_REG &= CNTL_MASK2;
  *TIMER_LOAD_REG = TIMER_MAX;
  return;
}

/**
 * @brief Called to check the value of the timer.
 *
 * @return timer's decrementing value
 */
uint32_t toc(void) {
  uint32_t result = *(TIMER_VAL_REG);
  return TIMER_MAX-result;
}

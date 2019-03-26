/**
 * @file   uart.c
 *
 * @brief  lower level hardware interactions for uart on pi
 *
 * @date   Feb.14th, 2018
 * @author David Dong <haochend@andrew.cmu.edu>
 */

#include <BCM2836.h>
#include <uart.h>
#include <gpio.h>
#include <kstdint.h>

/* Register physical addresses */
/** @brief physical address for AUXENB */
#define AUXENB (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x215004)
/** @brief physical address for IO */
#define AUX_MU_IO (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x215040)
/** @brief physical address for interrupt enable */
#define AUX_MU_IER (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x215044)
/** @brief physical address for baud rate */
#define AUX_MU_BAUD (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x215068)
/** @brief physical address for IIR */
#define AUX_MU_IIR (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x215048)
/** @brief physical address for LCR */
#define AUX_MU_LCR (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x21504c)
/** @brief physical address for LSR */
#define AUX_MU_LSR (volatile uint32_t *)(MMIO_BASE_PHYSICAL+0x215054)

/* Constances for calculation */
/** @brief baud rate given */
#define BAUD_RATE 115200
/** @brief system clock rate given */
#define CLOCK_FREQ 250000000

/** @brief Bit mask for choosing lower byte */
#define BYTE_MASK ((1<<8)-1)
/** @brief Bit mask for IIR */
#define IIR_MASK  6
/** @brief Bit mask for LCR */
#define LCR_MASK  3
/** @brief Bit mask for LSR */
#define LSR_CHECK (1<<5)


/**
 * @brief initializes UART to 115200 baud in 8-bit mode
 */
void uart_init(void) {
  // enable UART MMIO
  *AUXENB |= 1;

  // configure GPIO pullups
  gpio_set_pull(RX_PIN, GPIO_PULL_DISABLE);
  gpio_set_pull(TX_PIN, GPIO_PULL_DISABLE);
  // set GPIO pins to correct function on pg 102 of BCM2835 peripherals
  gpio_config(RX_PIN, GPIO_FUN_ALT5);
  gpio_config(TX_PIN, GPIO_FUN_ALT5);

  *AUX_MU_BAUD = (CLOCK_FREQ/(8*BAUD_RATE))-1;
  *AUX_MU_IER &= (~0) << 2;
  *AUX_MU_IIR = IIR_MASK;
  *AUX_MU_LCR |= LCR_MASK;
}

/**
 * @brief closes UART
 */
void uart_close(void) {
  *AUXENB &= (~0) << 1;
}


/**
 * @brief sends a byte over UART
 *
 * @param byte the byte to send
 */
void uart_put_byte(uint8_t byte) {
  while (((*AUX_MU_LSR)&LSR_CHECK) == 0) continue;
  *AUX_MU_IO = byte;
}


/**
 * @brief reads a byte over UART
 *
 * @return the byte received
 */
uint8_t uart_get_byte(void) {
  while (((*AUX_MU_LSR)&1) == 0) continue;
  return (*AUX_MU_IO)&BYTE_MASK;
}

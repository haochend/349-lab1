/**
 * @file   i2c.c
 *
 * @brief  I2C implementation on rpi 2
 *
 * @date   Feb.15th, 2018
 * @author David Dong <haochend@andrew.cmu.edu>
 */

#include <kstdint.h>
#include <gpio.h>
#include <i2c.h>
#include <BCM2836.h>

/* Register physical addresses */
/** @brief physical address for DIV */
#define BSC_DIV  (volatile uint32_t *)(MMIO_BASE_PHYSICAL + (0x804014))
/** @brief physical address for control */
#define BSC_C    (volatile uint32_t *)(MMIO_BASE_PHYSICAL + (0x804000))
/** @brief physical address for length */
#define BSC_DLEN (volatile uint32_t *)(MMIO_BASE_PHYSICAL + (0x804008))
/** @brief physical address for slave */
#define BSC_A    (volatile uint32_t *)(MMIO_BASE_PHYSICAL + (0x80400c))
/** @brief physical address for FIFO */
#define BSC_FIFO (volatile uint32_t *)(MMIO_BASE_PHYSICAL + (0x804010))
/** @brief physical address for status */
#define BSC_S    (volatile uint32_t *)(MMIO_BASE_PHYSICAL + (0x804004))

/** @brief Read mask */
#define READ_MASK ((1<<4) | 1 | (1<<7))
/** @brief Init mask */
#define INIT_MASK ((1<<15) | (1<<5) | (1<<4))
/** @brief FIFO mask */
#define FIFO_CLEAR (1<<4)
/** @brief Start mask */
#define START_MASK (1<<7)
/** @brief Write mask */
#define WRITE_MASK (~1)
/** @brief Done mask */
#define DONE_MASK (1<<1)

/** @brief Max length of buf */
#define MAX_LEN  16
/**
 * @brief initializes the I2C module
 *
 * @param clk bus clock speed, put this value directly into the
 *                CDIV register.
 */
void i2c_master_init(uint16_t clk) {
  gpio_set_pull(I2C1_SDA, GPIO_PULL_DISABLE);
  gpio_set_pull(I2C1_SCL, GPIO_PULL_DISABLE);
  gpio_config(I2C1_SDA, GPIO_FUN_ALT0);
  gpio_config(I2C1_SCL, GPIO_FUN_ALT0);

  *(BSC_DIV) = clk;
  *(BSC_C) |= INIT_MASK;
}

/**
 * @brief writes to I2C device
 *
 * @param buf pointer to output data buffer
 * @param len length of output data buffer in bytes
 * @param addr slave device address
 */
uint8_t i2c_master_write(uint8_t *buf, uint16_t len, uint8_t addr) {
  int i;
  if (len > MAX_LEN) return -1;

  *(BSC_DLEN) = len;
  *(BSC_A) = addr;
  *(BSC_C) |= FIFO_CLEAR;

  for (i = 0; i < len; i++) {
    *(BSC_FIFO) = buf[i];
  }
 
  *(BSC_C) &= WRITE_MASK;
  *(BSC_C) |= START_MASK;
  
  while ((*(BSC_S)&DONE_MASK) == 0) continue;

  unsigned x;
  x = *(BSC_S);
  *(BSC_S) = x;
 
  return 0;
}

/**
 * @brief reads from I2C device
 *
 * @param buf pointer to input data buffer
 * @param len number of bytes to read
 * @param addr slave device address
 */
uint8_t i2c_master_read(uint8_t *buf, uint16_t len, uint8_t addr) {
  int i;
  if (len > MAX_LEN) return -1;

  *BSC_DLEN = len;
  *BSC_A = addr;
  *BSC_C |= READ_MASK;

  while ((*(BSC_S)&DONE_MASK) == 0) continue;

  for (i = 0; i < len; i++) {
    buf[i] = *(BSC_FIFO);
  }

  unsigned x;
  x = *(BSC_S);
  *(BSC_S) = x;

  return 0;
}

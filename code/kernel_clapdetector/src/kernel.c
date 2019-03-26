
/**
 * @file   kernel.c
 *
 * @brief  entry point to the raspberry pi kernel
 *
 * @date   Feb.15th, 2018
 * @author David Dong <haochend@andrew.cmu.edu>
 */

#include <kstdint.h>
#include <ads1015.h>
#include <printk.h>
#include <uart.h>

/** @brief The threshold value for a detected clap */
#define Threshold 10000

/** @brief Audio channel identifier */
#define AUDIO_CHANNEL 2
/** @brief Light channel identifier */
#define LIGHT_CHANNEL 3

/**
 * @brief The kernel entry point
 */
void kernel_main(void) {
  uint8_t type;
  uint16_t reading;
  uart_init();
  adc_init();

  while (1) {
    printk("Enter a sensor to sample: ");
    type = uart_get_byte();
    printk("%c\n", type);

        switch (type) {
            case '0':
		adc_read(LIGHT_CHANNEL);
                reading = adc_read(LIGHT_CHANNEL);
                printk("Light: %d\n", reading);
                break;

            case '1':

                while (1) {
                    int i;
                    uint16_t minTemp = 0xFFFF;
                    uint16_t maxTemp = 0;

                    for (i = 0; i < 1000; i++) {
                        reading = adc_read(AUDIO_CHANNEL);
                        if (reading < minTemp)
                            minTemp = reading;
                        if (reading > maxTemp)
                            maxTemp = reading;
                    }

                    reading = maxTemp - minTemp;
                    printk("Audio: %d\n", reading);

                    if (reading > Threshold) {
                        printk("Clap Detected!\n");
                        break;
                    }
                }
                break;
        }
    }
}

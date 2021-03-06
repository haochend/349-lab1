/**
 * @file   kernel.c
 *
 * @brief  lab1 optimization part
 *
 * @date   9/20/2016
 * @author Kyuin Lee
 */

#include <arm.h>
#include <kstdint.h>
#include <uart.h>
#include <printk.h>
#include <tic_toc.h>
#include <printk.h>

/** @brief Size of arrays for optimize_me() and unoptimized() */
#define ARRSIZE 500
/** @brief Array of values for optimize_me() */
int array1[ARRSIZE];
/** @brief Array of values for unoptimized() */
int array2[ARRSIZE];

/** @brief Optimize this function! */
void optimize_me(int array[ARRSIZE]);
/** @brief Unoptimized function for reference */
void unoptimized(int array[ARRSIZE]);

/** @brief Entry point of the kernel */
void kernel_main(void)
{
  int i,good=1;
  uint32_t timerValue;

  uart_init();
  //initialize the two arrays
  for (i=0; i<ARRSIZE; i++)
  {
    array1[i] = i;
    array2[i] = i;
  }

  //Start measuring ticks for optimized function
  printk("+++++++Optimized Function+++++++\n");
  tic();
  optimize_me(array1);
  timerValue = toc();
  printk("%d\n",timerValue);

  //Start measuring ticks for unoptimized function
  printk("+++++++Unoptimized Function+++++++\n");
  tic();
  unoptimized(array2);
  timerValue = toc();
  printk("%d\n",timerValue);

  //checking the correctness.
  for (i=0; i<ARRSIZE; i++)
  {
    if (array1[i]!=array2[i])
    {
      //Print failed
      printk("+++++++Test Failed+++++++\n");
      good = 0;
      break;
    }
  }
  if (good)
  {
    //Print passed
    printk("+++++++Test Passed+++++++\n");
  }
  while (1)
  {
    delay_cycles(100000);
  };
}

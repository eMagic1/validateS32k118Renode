/*
 * Copyright (c) 2015 - 2016 , Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ###################################################################
**     Filename    : main.c
**     Project     : lptmr_pulse_counter_s32k116
**     Processor   : S32K116_48
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-03, 14:05, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "lpTmr1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif

volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */

#include <stdint.h>
#include <stdbool.h>

/* This define configures led pin and port for use with EVB, to make it run on
 * FVB you need to comment the following line.
 */
//#define EVB

#ifdef EVB
    #define LED_GREEN       15U   /* pin PTD15 - RGB LED on DEV-KIT */
    #define LED_GPIO_PORT   PTD   /* GPIO PORT D */
#else
    #define LED_GREEN       1U    /* pin PTC1 - LED1 on Motherboard */
    #define LED_GPIO_PORT   PTC   /* GPIO PORT C */
#endif

/*!
 * @brief: LPMR interrupt handler.
 *         When an interrupt occurs clear channel flag and toggle LED_GREEN
 */
void LPTMR_ISR(void)
{
    /* Clear compare flag */
    LPTMR_DRV_ClearCompareFlag(INST_LPTMR1);
    /* Toggle LED_GREEN */
    PINS_DRV_TogglePins(LED_GPIO_PORT, (1 << LED_GREEN));
}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - __start (startup asm routine)
 * - __init_hardware()
 * - main()
 *   - PE_low_level_init()
 *     - Common_Init()
 *     - Peripherals_Init()
*/
int main(void)
{

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                 /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

    /* Initialize and configure clocks
     *  -   configure system clocks
     *  -   enable and configure clocks for LPTMR, LED PORT
     */
    CLOCK_SYS_Init(g_clockManConfigsArr,   CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Initialize pins
     *  -   configure LED pin as output
     */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
    /* Turn off LED_GREEN */
    PINS_DRV_ClearPins(LED_GPIO_PORT, (1 << LED_GREEN));
    /* Init LPTMR as timer
     *  -   interrupt after 1 second
     *  -   SIRC as clock source
     *  -   counter disabled
     */
    LPTMR_DRV_Init(INST_LPTMR1, &lpTmr1_config0, false);

    /* Install IRQ handler for LPTMR interrupt */
    INT_SYS_InstallHandler(LPTMR0_IRQn, &LPTMR_ISR, (isr_t *)0);
    /* Enable IRQ for LPTMR */
    INT_SYS_EnableIRQ(LPTMR0_IRQn);

    /* Start LPTMR counter */
    LPTMR_DRV_StartCounter(INST_LPTMR1);

    /* Initialization complete, now the program will wait for interrupts from
     * LPTMR.
     */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/


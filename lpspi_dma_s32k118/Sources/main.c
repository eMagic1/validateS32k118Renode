/* 
 * Copyright 2018 NXP                                                                    
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
**     Project     : lpspi_dma_s32k118
**     Processor   : S32K118_100
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-07-18, 17:29, # CodeGen: 1
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
#include "Send.h"
#include "Receive.h"
#include "dmaController1.h"

  volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdint.h>
#include <stdbool.h>
#define TIMEOUT 1000U
#define NUMBER_OF_FRAMES 100U

/* Struct that defines RX and TX buffer arrays */
typedef struct
{
  uint8_t tx[NUMBER_OF_FRAMES];
  uint8_t rx[NUMBER_OF_FRAMES];
} spi_buffer_t;


/*!
* @brief Initialize the SPI buffer with different values for TX/RX
*
* @param spiBuffer Pointer to the buffer that will be initialized
* @param master    True if the buffer is used with the master device,
*                  False if not
*/
void InitSPIBuffer(spi_buffer_t * spiBuffer, bool master)
{
  uint8_t cnt;
  /* Fill the buffers */
  for(cnt = 0U; cnt < NUMBER_OF_FRAMES; cnt++)
  {
	  /* If the master flag is set, then the txBuffer will take the value of the counter,
	   * else the value will be (TRANSFER_SIZE - Counter).
	   * This approach is taken to make the data transfer more visible.
	   */
	  spiBuffer->tx[cnt] = ((master == true) ? (cnt) : (NUMBER_OF_FRAMES - cnt));
	  spiBuffer->rx[cnt] = 0U;
  }
}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/

  int main(void)
{
  /* Write your local variable definition here */
 spi_buffer_t master_buffer, slave_buffer;
 InitSPIBuffer(&master_buffer, true);
 InitSPIBuffer(&slave_buffer, false);
  /* Variable used for the loop that checks the data buffers */
 uint8_t i;
 /* Variable used to check if transfer was successful */
 volatile bool isTransferOk = true;
 /* Number of SPI transfers */
 volatile uint32_t count = 1000;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
  CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
  EDMA_DRV_Init(&dmaController1_State, &dmaController1_InitConfig0, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);
  /* SPI master configuration: clock speed: 500 kHz, 8 bits/frame, MSB first */
  LPSPI_DRV_MasterInit(SEND, &SendState, &Send_MasterConfig0);
  /* SPI slave configuration: clock spe DSPI_Mastered: 500 kHz, 8 bits/frame, MSB first */
  LPSPI_DRV_SlaveInit(RECEIVE, &ReceiveState, &Receive_SlaveConfig0);
  /* Configure delay between transfer, delay between SCK and PCS and delay between PCS and SCK */
  LPSPI_DRV_MasterSetDelay(SEND, 1, 1, 1);

 while(count)
 {
      LPSPI_DRV_SlaveTransfer(RECEIVE, slave_buffer.tx,slave_buffer.rx, NUMBER_OF_FRAMES);
      /* Start the blocking transfer */
      LPSPI_DRV_MasterTransferBlocking(SEND, master_buffer.tx,master_buffer.rx, NUMBER_OF_FRAMES, TIMEOUT);

      for(i=0;i<NUMBER_OF_FRAMES;i++)
      {
    	  if((master_buffer.rx[i]  != slave_buffer.tx[i])||(slave_buffer.rx[i]  != master_buffer.tx[i]))
    	  {
    		  isTransferOk = false;
    	  }
      }

      if(!isTransferOk)
      {
    	  break;
      }

      count--;
 }
 

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
**     for the NXP C55 series of microcontrollers.
**
** ###################################################################
*/

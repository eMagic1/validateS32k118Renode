/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : lpTmr1.h
**     Project     : lptmr_pulse_counter_s32k118
**     Processor   : S32K118_64
**     Component   : lptmr
**     Version     : Component SDK_S32K1xx_15, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K1xx_15
**     Compiler    : GNU C Compiler
**     Date/Time   : 2022-11-14, 22:29, # CodeGen: 0
**     Contents    :
**         LPTMR_DRV_InitConfigStruct       - void LPTMR_DRV_InitConfigStruct(lptmr_config_t *const config);
**         LPTMR_DRV_Init                   - void LPTMR_DRV_Init(const uint32_t instance,const lptmr_config_t *const...
**         LPTMR_DRV_SetConfig              - void LPTMR_DRV_SetConfig(const uint32_t instance,const lptmr_config_t * const...
**         LPTMR_DRV_GetConfig              - void LPTMR_DRV_GetConfig(const uint32_t instance,lptmr_config_t * const config);
**         LPTMR_DRV_Deinit                 - void LPTMR_DRV_Deinit(const uint32_t instance);
**         LPTMR_DRV_SetCompareValueByCount - status_t LPTMR_DRV_SetCompareValueByCount(const uint32_t instance,const...
**         LPTMR_DRV_GetCompareValueByCount - void LPTMR_DRV_GetCompareValueByCount(const uint32_t instance,uint16_t *...
**         LPTMR_DRV_SetCompareValueByUs    - status_t LPTMR_DRV_SetCompareValueByUs(const uint32_t instance,const uint16_t...
**         LPTMR_DRV_GetCompareValueByUs    - void LPTMR_DRV_GetCompareValueByUs(const uint32_t instance,uint16_t * const...
**         LPTMR_DRV_GetCompareFlag         - bool LPTMR_DRV_GetCompareFlag(const uint32_t instance);
**         LPTMR_DRV_ClearCompareFlag       - void LPTMR_DRV_ClearCompareFlag(const uint32_t instance);
**         LPTMR_DRV_IsRunning              - bool LPTMR_DRV_IsRunning(const uint32_t instance);
**         LPTMR_DRV_SetInterrupt           - void LPTMR_DRV_SetInterrupt(const uint32_t instance,const bool enableInterrupt);
**         LPTMR_DRV_GetCounterValueByCount - uint16_t LPTMR_DRV_GetCounterValueByCount(const uint32_t instance);
**         LPTMR_DRV_StartCounter           - void LPTMR_DRV_StartCounter(const uint32_t instance);
**         LPTMR_DRV_StopCounter            - void LPTMR_DRV_StopCounter(const uint32_t instance);
**         LPTMR_DRV_SetPinConfiguration    - void LPTMR_DRV_SetPinConfiguration(const uint32_t instance,const...
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc. 
**     Copyright 2016-2017 NXP 
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file lpTmr1.h
** @version 01.00
*/         
/*!
**  @addtogroup lpTmr1_module lpTmr1 module documentation
**  @{
*/         
#ifndef lpTmr1_H
#define lpTmr1_H
/* MODULE lpTmr1. */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, global macro not referenced
 * There are global macros defined to be used by the integrator and another one used as include guard.
 */

/* Include inherited beans */
#include "clockMan1.h"
#include "Cpu.h"
#include "lptmr_driver.h"

/*! @brief Device instance number */
#define INST_LPTMR1 0U


  
/*! @brief Configuration declaration */
extern const lptmr_config_t lpTmr1_config0;
    
#endif /* ifndef lpTmr1_H */
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

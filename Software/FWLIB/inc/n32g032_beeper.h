/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g032_beeper.h
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G032_BEEPER_H__
#define __N32G032_BEEPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g032.h"

/** @addtogroup N32G032_StdPeriph_Driver
 * @{
 */

/** @addtogroup BEEPER
 * @{
 */

/** @addtogroup BEEPER_Exported_Types
 * @{
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Exported_Constants
 * @{
 */

/** @addtogroup BUZZER_CLKSEL
 * @{
 */

#define BEEPER_BUZZER_CLKSEL_L1 ((uint32_t)0x00000001)
#define BEEPER_BUZZER_CLKSEL_L2 ((uint32_t)0x00000002)
#define BEEPER_BUZZER_CLKSEL_L3 ((uint32_t)0x00000003)
#define BEEPER_BUZZER_CLKSEL_L4 ((uint32_t)0x00000004)
#define BEEPER_BUZZER_CLKSEL_L5 ((uint32_t)0x00000005)
#define BEEPER_BUZZER_CLKSEL_L6 ((uint32_t)0x00000006)
#define BEEPER_BUZZER_CLKSEL_L7 ((uint32_t)0x00000007)

#define BEEPER_BUZZER_CLKSEL_M1 ((uint32_t)0x00000008)
#define BEEPER_BUZZER_CLKSEL_M2 ((uint32_t)0x00000009)
#define BEEPER_BUZZER_CLKSEL_M3 ((uint32_t)0x0000000A)
#define BEEPER_BUZZER_CLKSEL_M4 ((uint32_t)0x0000000B)
#define BEEPER_BUZZER_CLKSEL_M5 ((uint32_t)0x0000000C)
#define BEEPER_BUZZER_CLKSEL_M6 ((uint32_t)0x0000000D)
#define BEEPER_BUZZER_CLKSEL_M7 ((uint32_t)0x0000000E)

#define BEEPER_BUZZER_CLKSEL_H1 ((uint32_t)0x0000000F)
#define BEEPER_BUZZER_CLKSEL_H2 ((uint32_t)0x00000010)
#define BEEPER_BUZZER_CLKSEL_H3 ((uint32_t)0x00000011)
#define BEEPER_BUZZER_CLKSEL_H4 ((uint32_t)0x00000012)
#define BEEPER_BUZZER_CLKSEL_H5 ((uint32_t)0x00000013)
#define BEEPER_BUZZER_CLKSEL_H6 ((uint32_t)0x00000014)
#define BEEPER_BUZZER_CLKSEL_H7 ((uint32_t)0x00000015)

#define IS_BEEPER_BUZZER_CLKSEL(CLKSEL)                                                   \
     (((CLKSEL) >= BEEPER_BUZZER_CLKSEL_L1) && ((CLKSEL) <= BEEPER_BUZZER_CLKSEL_H7))

/** @addtogroup BUZZER_EN
 * @{
 */

#define BEEPER_BUZZER_BUZZER_ENABLE  ((uint32_t)0x00000020)
#define BEEPER_BUZZER_BUZZER_DISABLE ((uint32_t)0x00000000)

#define IS_BEEPER_BUZZER_EN(CONFIG)                                                       \
     (((CONFIG) == BEEPER_BUZZER_BUZZER_ENABLE) || ((CONFIG) == BEEPER_BUZZER_BUZZER_DISABLE))

/** @addtogroup INV_EN
 * @{
 */

#define BEEPER_INV_ENABLE  ((uint32_t)0x00000040)
#define BEEPER_INV_DISABLE ((uint32_t)0x00000000)

#define IS_BEEPER_INV_EN(CONFIG)                                                          \
     (((CONFIG) == BEEPER_INV_ENABLE) || ((CONFIG) == BEEPER_INV_DISABLE))

/** @addtogroup BEEPER_Exported_Constants
 * @{
 */

#define IS_BEEPER_ALL_PERIPH(PERIPH)                                                                                    \
    (((PERIPH) == BEEPER1) || ((PERIPH) == BEEPER2))
/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Exported_Macros
 * @{
 */
/**
 * @}
 */

/** @addtogroup BEEPER_Exported_Functions
 * @{
 */

void BEEPER_Init(BEEPER_Module* BEEPERx, uint32_t inv_en, uint32_t buzzer_clksel);
void BEEPER_Config(BEEPER_Module* BEEPERx, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /* __N32G032_BEEPER_H__ */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

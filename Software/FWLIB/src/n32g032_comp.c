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
 * @file n32g032_comp.c
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g032_comp.h"
#include "n32g032_rcc.h"

/** @addtogroup N32G032_StdPeriph_Driver
 * @{
 */

/** @addtogroup COMP
 * @brief COMP driver modules
 * @{
 */

/** @addtogroup COMP_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup COMP_Private_Functions
 * @{
 */
#define SetBitMsk(reg, bit, msk) ((reg) = ((reg) & ~(msk) | (bit)))
#define ClrBit(reg, bit)         ((reg) &= ~(bit))
#define SetBit(reg, bit)         ((reg) |= (bit))
#define GetBit(reg, bit)         ((reg) & (bit))
/**
 * @brief  Deinitializes the COMP peripheral registers to their default reset values.
 */
void COMP_DeInit(void)
{
    /* Reset All registers */
}

/**
 * @brief  Init COMP Struct
 * @note   This function can be used for N32G032 devices.
 * @param  COMP_InitStruct
 * @return none.
 */
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
    // COMP_CTRL
    COMP_InitStruct->ClockSelect   = COMP_CTRL_CLKSEL_SYSTEMCLK; // only COMP1 have this bit
    COMP_InitStruct->LowPoweMode   = COMP_CTRL_PWRMD_NORMAL;     // only COMP1 have this bit

    COMP_InitStruct->windowout     = false;                      // only COMP2 have this bit

    COMP_InitStruct->Blking        = COMP_CTRL_BLKING_NO;        /*see @ref COMP_CTRL_BLKING */
    COMP_InitStruct->Hyst          = COMP_CTRL_HYST_NO;          // see @COMPx_CTRL_HYST_MASK
    COMP_InitStruct->PolRev        = COMP_CTRL_POL_NONINVERTED;  // out polarity reverse
    COMP_InitStruct->OutTrg        = COMPx_CTRL_OUTTRG_NC;
    COMP_InitStruct->InpSel        = COMPx_CTRL_INPSEL_VREF2;    //Float as same with comp1 and comp2
    COMP_InitStruct->InmSel        = COMPx_CTRL_INMSEL_VREF2;    //NC as same with comp1 and comp2s
    // filter
    COMP_InitStruct->SampWindow    = COMPX_FILC_SAMPW_0;
    COMP_InitStruct->Thresh        = COMPX_FILC_THRESH_1;
    COMP_InitStruct->FilterEn      = COMPX_CTRL_FILEN_DISABLE;
    // filter psc
    COMP_InitStruct->ClkPsc        = COMP_FILP_CLKPSC_MASK;
}

/**
 * @brief  Init COMP register
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx
 * @param  COMP_InitStruct
 * @return none.
 */
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct)
{
    COMP_SingleType* pCS;
    __IO uint32_t tmp;
    if(COMPx == COMP1)
    {
        pCS = &COMP->Cmp1;
    }
    else if(COMPx == COMP2)
    {
        pCS = &COMP->Cmp2;
    }
    else
    {
        pCS = &COMP->Cmp3;
    }
    
    // filter
    tmp = pCS->FILC;
    tmp &= (~(uint32_t)(COMP_FILC_SAMPW_MASK | COMP_FILC_THRESH_MASK | COMP_FILC_FILEN_MASK));
    tmp |= (COMP_InitStruct->SampWindow | COMP_InitStruct->Thresh | COMP_InitStruct->FilterEn);
    pCS->FILC = tmp;

    // filter psc
    pCS->FILP = COMP_InitStruct->ClkPsc;

    // ctrl
    tmp = pCS->CTRL;
    if (COMPx == COMP1)
    {
        tmp &= (~(uint32_t)(COMP1_CTRL_CLKSEL_MASK | COMP1_CTRL_PWRMODE_MASK));
        tmp |= (COMP_InitStruct->ClockSelect | COMP_InitStruct->LowPoweMode);
    }
    else if (COMPx == COMP2) /* COMPx == COMP2 */
    {
        tmp &= (~(uint32_t)COMP2_CTRL_WINOUT_MASK);
        tmp |= COMP_InitStruct->windowout;
    }
    
    tmp &= (~(uint32_t)(COMP_CTRL_BLKING_MASK | COMP_CTRL_HYST_MASK | COMP_CTRL_POL_MASK | COMP_CTRL_OUTTRG_MASK
                      | COMP_CTRL_INPSEL_MASK | COMP_CTRL_INMSEL_MASK | COMP_CTRL_EN_MASK));
    tmp |= (COMP_InitStruct->Blking | COMP_InitStruct->Hyst | COMP_InitStruct->PolRev
          | COMP_InitStruct->OutTrg | COMP_InitStruct->InpSel | COMP_InitStruct->InmSel);

    pCS->CTRL = tmp;
}

/**
 * @brief  Enable COMPx x= 1 2 3
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx : COMP1/COMP2/COMP3
 * @param  Cmd   : COMP_CTRL_EN_ENABLE or COMP_CTRL_EN_DISABLE.
 * @return none.
 */
void COMP_Enable(COMPX COMPx, COMP_CTRL_EN_ENUM Cmd)
{
    if(COMPx == COMP1)
    {
        COMP->Cmp1.CTRL &= (~(uint32_t)COMP_CTRL_EN_MASK);
        COMP->Cmp1.CTRL |= Cmd;
    }
    else if(COMPx == COMP2)
    {
        COMP->Cmp2.CTRL &= (~(uint32_t)COMP_CTRL_EN_MASK);
        COMP->Cmp2.CTRL |= Cmd;
    }
    else
    {
        COMP->Cmp3.CTRL &= (~(uint32_t)COMP_CTRL_EN_MASK);
        COMP->Cmp3.CTRL |= Cmd;
    }
}

/**
 * @brief  Set INPSEL
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx  : COMP1/COMP2/COMP3
 * @param  Inpsel : COMP_CTRL_INPSEL.
 * @return none.
 */
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL_ENUM Inpsel)
{
    __IO uint32_t tmp;

    if(COMPx == COMP1)
    {
        tmp = COMP->Cmp1.CTRL;
    }
    else if(COMPx == COMP2)
    {
        tmp = COMP->Cmp2.CTRL;
    }
    else
    {
        tmp = COMP->Cmp3.CTRL;
    }
    
    tmp &= (~(uint32_t)COMP_CTRL_INPSEL_MASK);
    tmp |= Inpsel;
    
    if(COMPx == COMP1)
    {
        COMP->Cmp1.CTRL = tmp;
    }
    else if(COMPx == COMP2)
    {
        COMP->Cmp2.CTRL = tmp;
    }
    else
    {
        COMP->Cmp3.CTRL = tmp;
    }
}

/**
 * @brief  Set INMSEL
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx  : COMP1/COMP2/COMP3
 * @param  Inmsel : COMP_CTRL_INMSEL.
 * @return none.
 */
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL_ENUM Inmsel)
{
    __IO uint32_t tmp;

    if(COMPx == COMP1)
    {
        tmp = COMP->Cmp1.CTRL;
    }
    else if(COMPx == COMP2)
    {
        tmp = COMP->Cmp2.CTRL;
    }
    else 
    {
        tmp = COMP->Cmp3.CTRL;
    }
    
    tmp &= (~COMP_CTRL_INMSEL_MASK);
    tmp |= Inmsel;
    
    if(COMPx == COMP1)
    {
        COMP->Cmp1.CTRL = tmp;
    }
    else if(COMPx == COMP2)
    {
        COMP->Cmp2.CTRL = tmp;
    }
    else
    {
        COMP->Cmp3.CTRL = tmp;
    }
}

/**
 * @brief  Set OUTTRG
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx  : COMP1/COMP2/COMP3
 * @param  OutTrig : COMP_CTRL_OUTTRG.
 * @return none.
 */
void COMP_SetOutTrig(COMPX COMPx, COMP_CTRL_OUTTRG_ENUM OutTrig)
{
    __IO uint32_t tmp;

    if(COMPx == COMP1)
    {
        tmp = COMP->Cmp1.CTRL;
    }
    else if(COMPx == COMP2)
    {
        tmp = COMP->Cmp2.CTRL;
    }
    else
    {
        tmp = COMP->Cmp3.CTRL;
    }
    
    tmp &= (~(uint32_t)COMP_CTRL_OUTTRG_MASK);
    tmp |= OutTrig;
    
    if(COMPx == COMP1)
    {
        COMP->Cmp1.CTRL = tmp;
    }
    else if(COMPx == COMP2)
    {
        COMP->Cmp2.CTRL = tmp;
    }
    else
    {
        COMP->Cmp3.CTRL = tmp;
    }
}

/**
 * @brief  Enables or disables the specified COMPx(x = 1 2) interrupts.
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx_INT : COMP_INTEN_CMP1IEN_CFG or COMP_INTEN_CMP2IEN_CFG.
 * @param  Cmd       : ENABLE or DISABLE.
 * @return none.
 */
void COMP_ConfigInt(COMP_INTEN_CMPXIEN_ENUM COMPx_INT, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->INTEN |= (uint32_t)COMPx_INT;
    }
    else
    {
        COMP->INTEN &= (~(uint32_t)COMPx_INT);
    }
}

/**
 * @brief  Checks whether the specified COMPx(x = 1 2) interrupt has occurred or not
 * @note   This function can be used for N32G032 devices.
 * @param  status : COMP_INTSTS_CMP2IS_STATUS or COMP_INTSTS_CMP1IS_STATUS
 * @return The new state of COMP_INT (SET or RESET).
 */
INTStatus COMP_GetIntStatus(COMP_INTSTS_STATUS_ENUM status)
{
    INTStatus bitstatus = RESET;

    if ((COMP->INTSTS & status) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
 * @brief  Config COMP WindowMode.
 * @note   This function can be used for N32G032 devices.
 * @param  comp_WinMdInSel : COMP_WINMODE_WINMDINSEL_PA1 or COMP_WINMODE_WINMDINSEL_PA3.
 * @param  Cmd             : COMP_WINMODE_CMP12MD_ENABLE or COMP_WINMODE_CMP12MD_DISABLE.
 * @return none.
 */
void COMP_ConfigWindowMode(COMP_WINMODE_WINMDINSEL_ENUM WinMdInSel, COMP_WINMODE_CMP12MD_ENUM Cmd)
{
    __IO uint32_t tmp = 0;

    tmp = COMP->WINMODE;

    tmp &= (~COMP_WINMODE_WINMDINSEL_MASK);
    tmp |= WinMdInSel;

    COMP->WINMODE = tmp;
}

/**
 * @brief  Checks COMPx(x = 1 2) out status.
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx : COMP1/COMP2/COMP3
 * @return The new state of COMPx_CTRL_OUT (SET or RESET).
 */
FlagStatus COMP_GetCompOutStatus(COMPX COMPx)
{
    FlagStatus bitstatus = RESET;
  
    __IO uint32_t tmp;

    if(COMPx == COMP1)
    {
        if ((COMP->Cmp1.CTRL & COMP_CTRL_OUT_MASK) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else if(COMPx == COMP2)
    {
        if ((COMP->Cmp2.CTRL & COMP_CTRL_OUT_MASK) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((COMP->Cmp3.CTRL & COMP_CTRL_OUT_MASK) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}

/**
 * @brief  Config COMPx_CTRL register read-only.
 * @note   This function can be used for N32G032 devices.
 * @param  COMPx_LOCK : COMP_LOCK_CMP1LK_LOCK/COMP_LOCK_CMP1LK_UNLOCK
 *                     /COMP_LOCK_CMP2LK_LOCK/COMP_LOCK_CMP2LK_UNLOCK
 *                     /COMP_LOCK_CMP3LK_LOCK/COMP_LOCK_CMP3LK_UNLOCK
 * @param  Cmd        : ENABLE or DISABLE.
 * @return none.
 */
void COMP_ConfigCTRLLock(COMP_LOCK_CMPXLK_ENUM COMPx_LOCK, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->LOCK |= (uint32_t)COMPx_LOCK;
    }
    else
    {
        COMP->LOCK &= (~(uint32_t)COMPx_LOCK);
    }
}

/**
 * @brief  Config COMPx_CTRL register read-only.
 * @note   This function can be used for N32G032 devices.
 * @param  Vrefx      : VREF1/VREF2
 * @param  COMP_VREFx : COMP_INVREF_VREFXSEL_ENUM
 * @param  Cmd        : ENABLE or DISABLE.
 * @return none.
 */
void COMP_ConfigVREFx(VREFX_ENUM Vrefx, COMP_INVREF_VREFXSEL_ENUM COMP_VREFx, FunctionalState Cmd)
{
    if(Vrefx == VREF1)
    {
        COMP->INVREF &= (~COMP_INVREF_VREF1SEL_MSK);
        COMP->INVREF |= COMP_VREFx;
        if(Cmd != DISABLE)
        {
            COMP->INVREF |= COMP_INVREF_VREF1EN_ENABLE;
        }
        else
        {
            COMP->INVREF &= (~(uint32_t)COMP_INVREF_VREF1EN_ENABLE);
        }
    }
    else
    {
        COMP->INVREF &= (~COMP_INVREF_VREF2SEL_MSK);
        COMP->INVREF |= COMP_VREFx;
        if(Cmd != DISABLE)
        {
            COMP->INVREF |= COMP_INVREF_VREF2EN_ENABLE;
        }
        else
        {
            COMP->INVREF &= (~(uint32_t)COMP_INVREF_VREF2EN_ENABLE);
        }
    }
}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

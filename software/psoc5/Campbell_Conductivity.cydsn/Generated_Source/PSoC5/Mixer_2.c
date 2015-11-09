/*******************************************************************************
* File Name: Mixer_2.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the MIXER Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Mixer_2.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL)
    #include "Mixer_2_aclk.h"
#endif /* Mixer_2_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 Mixer_2_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static Mixer_2_backupStruct Mixer_2_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Mixer_2_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Mixer_2_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Mixer_2_Init(void) 
{
    float LOf = Mixer_2_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (Mixer_2_MIXER_TYPE == Mixer_2_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Mixer_2_CR0_REG = Mixer_2_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        Mixer_2_CR1_REG = (Mixer_2_COMP_4P35PF  |
                                Mixer_2_DIV2_DISABLE |
                                Mixer_2_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < Mixer_2_LO_CLOCK_FREQ_100_KHz)
        {
            Mixer_2_CR2_REG = (Mixer_2_BIAS_LOW |
										Mixer_2_REDC_01 |
										Mixer_2_GNDVREF_DI |
										Mixer_2_R20_40B_40K);
        }
        else
        {
            Mixer_2_CR2_REG = (Mixer_2_BIAS_LOW |
										Mixer_2_REDC_01 |
										Mixer_2_GNDVREF_DI |
										Mixer_2_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Mixer_2_CR0_REG = Mixer_2_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        Mixer_2_CR1_REG = (Mixer_2_COMP_4P35PF  |
                                Mixer_2_DIV2_ENABLE |
                                Mixer_2_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < Mixer_2_LO_CLOCK_FREQ_100_KHz)
        {
            Mixer_2_CR2_REG = (Mixer_2_BIAS_LOW |
										Mixer_2_GNDVREF_DI |
										Mixer_2_R20_40B_40K |
										Mixer_2_RVAL_40K); 
        }
        else
        {
            Mixer_2_CR2_REG = (Mixer_2_BIAS_LOW |
										Mixer_2_GNDVREF_DI |
										Mixer_2_R20_40B_20K |
										Mixer_2_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    Mixer_2_CLK_REG |= Mixer_2_CLK_EN;

    /* Set default power */
    Mixer_2_SetPower(Mixer_2_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL)
        Mixer_2_aclk_SetMode(CYCLK_DUTY);
    #endif /* Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: Mixer_2_Enable
********************************************************************************
*  
* Summary: 
*  Enables the Mixer block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Mixer_2_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(Mixer_2_P5backup.enableState == 1u)
        {
            Mixer_2_CR1_REG = Mixer_2_P5backup.scCR1Reg;
            Mixer_2_CR2_REG = Mixer_2_P5backup.scCR2Reg;
            Mixer_2_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    Mixer_2_PM_ACT_CFG_REG |= Mixer_2_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    Mixer_2_PM_STBY_CFG_REG |= Mixer_2_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        Mixer_2_PWRMGR_ACLK_REG |= Mixer_2_ACT_PWR_ACLK_EN;        
        Mixer_2_STBY_PWRMGR_ACLK_REG |= Mixer_2_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        Mixer_2_aclk_Enable();        
    #endif /* Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL */

    Mixer_2_PUMP_CR1_REG |= Mixer_2_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                Mixer_2_BSTCLK_REG &= (uint8)(~Mixer_2_BST_CLK_INDEX_MASK);
                Mixer_2_BSTCLK_REG |= Mixer_2_BST_CLK_EN | CyScBoostClk__INDEX;
                Mixer_2_SC_MISC_REG |= Mixer_2_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                Mixer_2_BSTCLK_REG &= (uint8)(~Mixer_2_BST_CLK_EN);
                Mixer_2_SC_MISC_REG &= (uint8)(~Mixer_2_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: Mixer_2_Start
********************************************************************************
*
* Summary:
*  The start function initializes the SC block control registers based on the
*  Mixer type selected and and enables power to the SC block
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Global variables:
*  Mixer_2_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  Mixer_2_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void Mixer_2_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Mixer_2_initVar == 0u)
    {
        Mixer_2_Init();
        Mixer_2_initVar = 1u;
    }
    /* Enable the power to the block */
    Mixer_2_Enable();
    
}


/*******************************************************************************
* Function Name: Mixer_2_Stop
********************************************************************************
*
* Summary:
*  Disables power to SC block.
*
* Parameters:  
*  void 
*
* Return: 
*  void 
*
*******************************************************************************/
void Mixer_2_Stop(void) 
{       
    /* Disble power to the Amp in Active mode template */
    Mixer_2_PM_ACT_CFG_REG &= (uint8)(~Mixer_2_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    Mixer_2_PM_STBY_CFG_REG &= (uint8)(~Mixer_2_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            Mixer_2_BSTCLK_REG &= (uint8)(~Mixer_2_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((Mixer_2_PM_ACT_CFG_REG & Mixer_2_PM_ACT_CFG_MASK) == 0u)
            {
                Mixer_2_SC_MISC_REG &= (uint8)(~Mixer_2_PUMP_FORCE);
                Mixer_2_PUMP_CR1_REG &= (uint8)(~Mixer_2_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        Mixer_2_P5backup.scCR1Reg = Mixer_2_CR1_REG;
        Mixer_2_P5backup.scCR2Reg = Mixer_2_CR2_REG;
        Mixer_2_CR1_REG = 0x00u;
        Mixer_2_CR2_REG = 0x00u;
        Mixer_2_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        Mixer_2_PWRMGR_ACLK_REG &= (uint8)(~Mixer_2_ACT_PWR_ACLK_EN);
        Mixer_2_STBY_PWRMGR_ACLK_REG &= (uint8)(~Mixer_2_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        Mixer_2_aclk_Disable();
    #endif /* Mixer_2_LO_SOURCE == Mixer_2_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: Mixer_2_SetPower
********************************************************************************
*
* Summary:
*  Set the drive power of the MIXER
*
* Parameters:  
*  power:  Sets power level between (0) and (3) high power
*
* Return: 
*  void 
*
*******************************************************************************/
void Mixer_2_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = Mixer_2_CR1_REG & (uint8)(~Mixer_2_DRIVE_MASK);
    tmpCR |= (power & Mixer_2_DRIVE_MASK);
    Mixer_2_CR1_REG = tmpCR;  
}


/* [] END OF FILE */

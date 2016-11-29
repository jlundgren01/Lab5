/*******************************************************************************
* File Name: GND.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "GND.h"

static GND_BACKUP_STRUCT  GND_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: GND_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet GND_SUT.c usage_GND_Sleep_Wakeup
*******************************************************************************/
void GND_Sleep(void)
{
    #if defined(GND__PC)
        GND_backup.pcState = GND_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            GND_backup.usbState = GND_CR1_REG;
            GND_USB_POWER_REG |= GND_USBIO_ENTER_SLEEP;
            GND_CR1_REG &= GND_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GND__SIO)
        GND_backup.sioState = GND_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        GND_SIO_REG &= (uint32)(~GND_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: GND_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to GND_Sleep() for an example usage.
*******************************************************************************/
void GND_Wakeup(void)
{
    #if defined(GND__PC)
        GND_PC = GND_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            GND_USB_POWER_REG &= GND_USBIO_EXIT_SLEEP_PH1;
            GND_CR1_REG = GND_backup.usbState;
            GND_USB_POWER_REG &= GND_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GND__SIO)
        GND_SIO_REG = GND_backup.sioState;
    #endif
}


/* [] END OF FILE */

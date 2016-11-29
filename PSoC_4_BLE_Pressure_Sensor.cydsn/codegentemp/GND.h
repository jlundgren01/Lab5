/*******************************************************************************
* File Name: GND.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_GND_H) /* Pins GND_H */
#define CY_PINS_GND_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GND_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} GND_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GND_Read(void);
void    GND_Write(uint8 value);
uint8   GND_ReadDataReg(void);
#if defined(GND__PC) || (CY_PSOC4_4200L) 
    void    GND_SetDriveMode(uint8 mode);
#endif
void    GND_SetInterruptMode(uint16 position, uint16 mode);
uint8   GND_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GND_Sleep(void); 
void GND_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GND__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GND_DRIVE_MODE_BITS        (3)
    #define GND_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GND_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GND_SetDriveMode() function.
         *  @{
         */
        #define GND_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GND_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GND_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GND_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GND_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GND_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GND_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GND_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GND_MASK               GND__MASK
#define GND_SHIFT              GND__SHIFT
#define GND_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GND_SetInterruptMode() function.
     *  @{
     */
        #define GND_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GND_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GND_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GND_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GND__SIO)
    #define GND_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GND__PC) && (CY_PSOC4_4200L)
    #define GND_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GND_USBIO_DISABLE              ((uint32)(~GND_USBIO_ENABLE))
    #define GND_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GND_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GND_USBIO_ENTER_SLEEP          ((uint32)((1u << GND_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GND_USBIO_SUSPEND_DEL_SHIFT)))
    #define GND_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GND_USBIO_SUSPEND_SHIFT)))
    #define GND_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GND_USBIO_SUSPEND_DEL_SHIFT)))
    #define GND_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GND__PC)
    /* Port Configuration */
    #define GND_PC                 (* (reg32 *) GND__PC)
#endif
/* Pin State */
#define GND_PS                     (* (reg32 *) GND__PS)
/* Data Register */
#define GND_DR                     (* (reg32 *) GND__DR)
/* Input Buffer Disable Override */
#define GND_INP_DIS                (* (reg32 *) GND__PC2)

/* Interrupt configuration Registers */
#define GND_INTCFG                 (* (reg32 *) GND__INTCFG)
#define GND_INTSTAT                (* (reg32 *) GND__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GND_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GND__SIO)
    #define GND_SIO_REG            (* (reg32 *) GND__SIO)
#endif /* (GND__SIO_CFG) */

/* USBIO registers */
#if !defined(GND__PC) && (CY_PSOC4_4200L)
    #define GND_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GND_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GND_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GND_DRIVE_MODE_SHIFT       (0x00u)
#define GND_DRIVE_MODE_MASK        (0x07u << GND_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GND_H */


/* [] END OF FILE */

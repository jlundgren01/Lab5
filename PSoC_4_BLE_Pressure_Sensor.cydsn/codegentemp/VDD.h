/*******************************************************************************
* File Name: VDD.h  
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

#if !defined(CY_PINS_VDD_H) /* Pins VDD_H */
#define CY_PINS_VDD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VDD_aliases.h"


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
} VDD_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VDD_Read(void);
void    VDD_Write(uint8 value);
uint8   VDD_ReadDataReg(void);
#if defined(VDD__PC) || (CY_PSOC4_4200L) 
    void    VDD_SetDriveMode(uint8 mode);
#endif
void    VDD_SetInterruptMode(uint16 position, uint16 mode);
uint8   VDD_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VDD_Sleep(void); 
void VDD_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VDD__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VDD_DRIVE_MODE_BITS        (3)
    #define VDD_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VDD_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VDD_SetDriveMode() function.
         *  @{
         */
        #define VDD_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VDD_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VDD_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VDD_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VDD_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VDD_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VDD_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VDD_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VDD_MASK               VDD__MASK
#define VDD_SHIFT              VDD__SHIFT
#define VDD_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VDD_SetInterruptMode() function.
     *  @{
     */
        #define VDD_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VDD_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VDD_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VDD_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VDD__SIO)
    #define VDD_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VDD__PC) && (CY_PSOC4_4200L)
    #define VDD_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VDD_USBIO_DISABLE              ((uint32)(~VDD_USBIO_ENABLE))
    #define VDD_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VDD_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VDD_USBIO_ENTER_SLEEP          ((uint32)((1u << VDD_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VDD_USBIO_SUSPEND_DEL_SHIFT)))
    #define VDD_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VDD_USBIO_SUSPEND_SHIFT)))
    #define VDD_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VDD_USBIO_SUSPEND_DEL_SHIFT)))
    #define VDD_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VDD__PC)
    /* Port Configuration */
    #define VDD_PC                 (* (reg32 *) VDD__PC)
#endif
/* Pin State */
#define VDD_PS                     (* (reg32 *) VDD__PS)
/* Data Register */
#define VDD_DR                     (* (reg32 *) VDD__DR)
/* Input Buffer Disable Override */
#define VDD_INP_DIS                (* (reg32 *) VDD__PC2)

/* Interrupt configuration Registers */
#define VDD_INTCFG                 (* (reg32 *) VDD__INTCFG)
#define VDD_INTSTAT                (* (reg32 *) VDD__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VDD_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VDD__SIO)
    #define VDD_SIO_REG            (* (reg32 *) VDD__SIO)
#endif /* (VDD__SIO_CFG) */

/* USBIO registers */
#if !defined(VDD__PC) && (CY_PSOC4_4200L)
    #define VDD_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VDD_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VDD_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VDD_DRIVE_MODE_SHIFT       (0x00u)
#define VDD_DRIVE_MODE_MASK        (0x07u << VDD_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VDD_H */


/* [] END OF FILE */

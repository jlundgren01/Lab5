/*******************************************************************************
* File Name: GND.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_GND_ALIASES_H) /* Pins GND_ALIASES_H */
#define CY_PINS_GND_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GND_0			(GND__0__PC)
#define GND_0_PS		(GND__0__PS)
#define GND_0_PC		(GND__0__PC)
#define GND_0_DR		(GND__0__DR)
#define GND_0_SHIFT	(GND__0__SHIFT)
#define GND_0_INTR	((uint16)((uint16)0x0003u << (GND__0__SHIFT*2u)))

#define GND_INTR_ALL	 ((uint16)(GND_0_INTR))


#endif /* End Pins GND_ALIASES_H */


/* [] END OF FILE */

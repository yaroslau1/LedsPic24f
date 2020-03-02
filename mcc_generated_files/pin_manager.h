/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  PIC24FJ128GC010
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB 	          :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RF2, high using LATF2.

  @Description
    Sets the GPIO pin, RF2, high using LATF2.

  @Preconditions
    The RF2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF2 high (1)
    IO_RF2_SetHigh();
    </code>

*/
#define IO_RF2_SetHigh()          (_LATF2 = 1)
/**
  @Summary
    Sets the GPIO pin, RF2, low using LATF2.

  @Description
    Sets the GPIO pin, RF2, low using LATF2.

  @Preconditions
    The RF2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF2 low (0)
    IO_RF2_SetLow();
    </code>

*/
#define IO_RF2_SetLow()           (_LATF2 = 0)
/**
  @Summary
    Toggles the GPIO pin, RF2, using LATF2.

  @Description
    Toggles the GPIO pin, RF2, using LATF2.

  @Preconditions
    The RF2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF2
    IO_RF2_Toggle();
    </code>

*/
#define IO_RF2_Toggle()           (_LATF2 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RF2.

  @Description
    Reads the value of the GPIO pin, RF2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF2
    postValue = IO_RF2_GetValue();
    </code>

*/
#define IO_RF2_GetValue()         _RF2
/**
  @Summary
    Configures the GPIO pin, RF2, as an input.

  @Description
    Configures the GPIO pin, RF2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF2 as an input
    IO_RF2_SetDigitalInput();
    </code>

*/
#define IO_RF2_SetDigitalInput()  (_TRISF2 = 1)
/**
  @Summary
    Configures the GPIO pin, RF2, as an output.

  @Description
    Configures the GPIO pin, RF2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF2 as an output
    IO_RF2_SetDigitalOutput();
    </code>

*/
#define IO_RF2_SetDigitalOutput() (_TRISF2 = 0)
/**
  @Summary
    Sets the GPIO pin, RF3, high using LATF3.

  @Description
    Sets the GPIO pin, RF3, high using LATF3.

  @Preconditions
    The RF3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF3 high (1)
    IO_RF3_SetHigh();
    </code>

*/
#define IO_RF3_SetHigh()          (_LATF3 = 1)
/**
  @Summary
    Sets the GPIO pin, RF3, low using LATF3.

  @Description
    Sets the GPIO pin, RF3, low using LATF3.

  @Preconditions
    The RF3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF3 low (0)
    IO_RF3_SetLow();
    </code>

*/
#define IO_RF3_SetLow()           (_LATF3 = 0)
/**
  @Summary
    Toggles the GPIO pin, RF3, using LATF3.

  @Description
    Toggles the GPIO pin, RF3, using LATF3.

  @Preconditions
    The RF3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF3
    IO_RF3_Toggle();
    </code>

*/
#define IO_RF3_Toggle()           (_LATF3 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RF3.

  @Description
    Reads the value of the GPIO pin, RF3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF3
    postValue = IO_RF3_GetValue();
    </code>

*/
#define IO_RF3_GetValue()         _RF3
/**
  @Summary
    Configures the GPIO pin, RF3, as an input.

  @Description
    Configures the GPIO pin, RF3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF3 as an input
    IO_RF3_SetDigitalInput();
    </code>

*/
#define IO_RF3_SetDigitalInput()  (_TRISF3 = 1)
/**
  @Summary
    Configures the GPIO pin, RF3, as an output.

  @Description
    Configures the GPIO pin, RF3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF3 as an output
    IO_RF3_SetDigitalOutput();
    </code>

*/
#define IO_RF3_SetDigitalOutput() (_TRISF3 = 0)

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ128GC010
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);



#endif

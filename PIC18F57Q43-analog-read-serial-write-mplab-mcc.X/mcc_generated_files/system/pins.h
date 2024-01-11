/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define POT_TRIS                 TRISAbits.TRISA0
#define POT_LAT                  LATAbits.LATA0
#define POT_PORT                 PORTAbits.RA0
#define POT_WPU                  WPUAbits.WPUA0
#define POT_OD                   ODCONAbits.ODCA0
#define POT_ANS                  ANSELAbits.ANSELA0
#define POT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POT_GetValue()           PORTAbits.RA0
#define POT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define POT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define POT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define POT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define POT_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define POT_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RF0 aliases
#define TX_TRIS                 TRISFbits.TRISF0
#define TX_LAT                  LATFbits.LATF0
#define TX_PORT                 PORTFbits.RF0
#define TX_WPU                  WPUFbits.WPUF0
#define TX_OD                   ODCONFbits.ODCF0
#define TX_ANS                  ANSELFbits.ANSELF0
#define TX_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define TX_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define TX_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define TX_GetValue()           PORTFbits.RF0
#define TX_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define TX_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define TX_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define TX_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define TX_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define TX_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define TX_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define RX_TRIS                 TRISFbits.TRISF1
#define RX_LAT                  LATFbits.LATF1
#define RX_PORT                 PORTFbits.RF1
#define RX_WPU                  WPUFbits.WPUF1
#define RX_OD                   ODCONFbits.ODCF1
#define RX_ANS                  ANSELFbits.ANSELF1
#define RX_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define RX_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define RX_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define RX_GetValue()           PORTFbits.RF1
#define RX_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define RX_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define RX_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define RX_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define RX_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define RX_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define RX_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/
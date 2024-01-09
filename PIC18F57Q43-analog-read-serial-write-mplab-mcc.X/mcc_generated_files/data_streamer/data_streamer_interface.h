/**
 * DATASTREAMER Generated Driver Interface API Header File.
 * 
 * @file data_streamer_interface.h
 * 
 * @ingroup datastreamer
 * 
 * @brief This declares the interface contract between the Data Streamer driver and the selected UART peripheral.
 * 
 * @version Data Streamer Driver Version 1.2.0
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

#ifndef DATA_STREAMER_INTERFACE_H
#define	DATA_STREAMER_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @ingroup datastreamer
 * @struct data_streamer_interface_t 
 * @brief Structure containing the function pointers to the Data Streamer communications APIs.
 */
typedef struct
{
    void (*Write)(uint8_t);
    bool(*IsTxReady)(void);
    bool(*IsTxDone)(void);
} data_streamer_interface_t;

/**
 * @ingroup datastreamer
 * @struct DATA_STREAMER 
 * @brief Abstraction interface for the UART peripheral.
 */
extern const data_streamer_interface_t DATA_STREAMER;

#endif	/* DATA_STREAMER_INTERFACE_H */
/**
 End of File
*/
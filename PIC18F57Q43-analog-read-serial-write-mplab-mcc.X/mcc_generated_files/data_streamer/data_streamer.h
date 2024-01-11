
/**
 * DATASTREAMER Generated Driver API Header File.
 *
 * @file data_streamer.h
 * 
 * @defgroup datastreamer DATASTREAMER
 * 
 * @brief This file contains the API prototypes and the related data structures for the Data Streamer driver.
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

#ifndef DATA_STREAMER_H
#define	DATA_STREAMER_H

#include "data_streamer_interface.h"
#include <stdio.h>

/**  
 * @def Data Streamer Start Byte Macro.
 * Macro that represents the byte that is sent to signify the beginning of the Data Streamer frame.
 */
#define DATA_STREAMER_START_BYTE 3

/**  
 * @def Data Streamer End Byte Macro.
 * Macro that represents the byte that is sent to signify the end of the Data Streamer frame.
 */
#define DATA_STREAMER_END_BYTE (255 - DATA_STREAMER_START_BYTE)

/**
 * @ingroup datastreamer
 * @struct DATA_STREAMER_STRUCT
 * @brief Structure containing the initial Data Streamer variables.
 */
struct __attribute__((packed)) DATA_STREAMER_STRUCT
{
    uint16_t Measurement;
    int16_t Inverse;
    int8_t Counter;
};

/**
 * @ingroup datastreamer
 * @struct PACKAGE_STRUCT
 * @brief Structure containing a pointer assigned to a custom data package and its size which are set by the user.
 */
struct PACKAGE_STRUCT
{
    void * varStruct;
    size_t length;
};

/**
 * @ingroup datastreamer
 * @struct DataStreamer
 * @brief An instance of the DATA_STREAMER_STRUCT.
 */
extern struct DATA_STREAMER_STRUCT DataStreamer;

/**
 @ingroup datastreamer
 @struct DATA_STREAMER_PACKAGE
 @brief An instance of the PACKAGE_STRUCT.
 */
extern struct PACKAGE_STRUCT DATA_STREAMER_PACKAGE;

/**  
 * @def Data Streamer Write Frame Macro.
 * Macro used to write the frame to the Data Streamer.
 */
#define WriteFrame() DataStreamer_FrameSend(DATA_STREAMER_PACKAGE.varStruct,DATA_STREAMER_PACKAGE.length);

/**
 * @ingroup datastreamer
 * @brief  Initializes the Data Streamer.
 * @param None.
 * @return None.
 */ 
void DataStreamer_Initialize(void);

/**
 * @ingroup datastreamer
 * @brief  Writes the frame to the Data Streamer.
 * @param void * package - Pointer to the DATA_STREAMER_PACKAGE structure containing the variables to be sent.
 * @param size_t length - Size of the DATA_STREAMER_PACKAGE structure in bytes.
 * @return None.
 */ 
void DataStreamer_FrameSend(void * package, size_t length);

/**
 * @ingroup datastreamer
 * @brief  Sets the package containing the variables to be sent by the Data Streamer.
 * @param void * customStructHandler - Pointer to the user-defined structure containing the variables to be sent to the Data Streamer.
 * @param size_t customlength - Size of the user-defined structure in bytes.
 * @return None.
 */ 
void DataStreamer_PackageSet(void * customStructHandler, size_t customlength);

#endif	/* DATA_STREAMER_H */
/**
 End of File
*/
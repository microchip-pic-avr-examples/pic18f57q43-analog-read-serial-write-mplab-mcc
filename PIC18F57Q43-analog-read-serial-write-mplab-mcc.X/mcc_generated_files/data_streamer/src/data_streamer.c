// Generate variable frames for sending data to the MPLAB Data Visualizer, 
// e.g. to be display on a graph.
#include <stdint.h>
#include "../../uart/uart3.h"

#include "../../data_streamer/data_streamer.h" // Issue #1 - please log MCC bug.

#define DATA_STREAMER_START_BYTE 3  //trivial Data Streamer Protocol start of frame token
#define DATA_STREAMER_END_BYTE (255 - DATA_STREAMER_START_BYTE)  
// Data Streamer Protocol end byte is the One's compliment (~) of startByte, 
// e.g. startByte: 0b0000 0011, endByte: 0b1111 1100

static void variableWrite_sendValue(uint8_t* byte_ptr, uint8_t num_bytes)
 {
      for(uint8_t i = 0; i < num_bytes; i++)
      {
         UART3_Write(byte_ptr[i]);
      }
}

void variableWrite_sendFrame(uint16_t measurement)
{
   UART3_Write(DATA_STREAMER_START_BYTE);  

   UART3_Write((measurement >> 0)  & 0xFF); // Low  byte of uint16_t 
   UART3_Write((measurement >> 8)  & 0xFF); // High byte

   UART3_Write(DATA_STREAMER_END_BYTE);  

   while(!UART3_IsTxDone());
}

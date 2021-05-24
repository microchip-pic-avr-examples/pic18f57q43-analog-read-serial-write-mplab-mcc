/**
  UART3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart3.c

  @Summary
    This is the generated driver implementation file for the UART3 driver using CCL

  @Description
    This source file provides APIs for UART3.
    Generation Information :
        Driver Version    :  2.4.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.2
        MPLAB             :  Standalone
*/

/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "../uart3.h"

const struct UART_INTERFACE UART3_Interface = {
  .Initialize = UART3_Initialize,
  .Write = UART3_Write,
  .Read = UART3_Read,
  .RxCompleteCallbackRegister = NULL,
  .TxCompleteCallbackRegister = NULL,
  .ErrorCallbackRegister = UART3_SetErrorHandler,
  .FramingErrorCallbackRegister = UART3_SetFramingErrorHandler,
  .OverrunErrorCallbackRegister = UART3_SetOverrunErrorHandler,
  .ParityErrorCallbackRegister = NULL,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = UART3_IsRxReady,
  .IsTxReady = UART3_IsTxReady,
  .IsTxDone = UART3_IsTxDone
};

/**
  Section: Macro Declarations
*/
#define UART3_TX_BUFFER_SIZE 8
#define UART3_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
*/

static volatile uint8_t uart3TxHead = 0;
static volatile uint8_t uart3TxTail = 0;
static volatile uint8_t uart3TxBuffer[UART3_TX_BUFFER_SIZE];
volatile uint8_t uart3TxBufferRemaining;

static volatile uint8_t uart3RxHead = 0;
static volatile uint8_t uart3RxTail = 0;
static volatile uint8_t uart3RxBuffer[UART3_RX_BUFFER_SIZE];
static volatile uart3_status_t uart3RxStatusBuffer[UART3_RX_BUFFER_SIZE];
volatile uint8_t uart3RxCount;
static volatile uart3_status_t uart3RxLastError;

/**
  Section: UART3 APIs
*/
void (*UART3_FramingErrorHandler)(void);
void (*UART3_OverrunErrorHandler)(void);
void (*UART3_ErrorHandler)(void);

void UART3_DefaultFramingErrorHandler(void);
void UART3_DefaultOverrunErrorHandler(void);
void UART3_DefaultErrorHandler(void);

void UART3_Initialize(void)
{
    // Disable interrupts before changing states
    PIE9bits.U3RXIE = 0;
    UART3_SetRxInterruptHandler(UART3_Receive_ISR);
    PIE9bits.U3TXIE = 0;
    UART3_SetTxInterruptHandler(UART3_Transmit_ISR);
    PIE9bits.U3EIE = 0;
    UART3_SetFramingErrorInterruptHandler(UART3_FramingError_ISR);
    PIE9bits.U3IE = 0;
    UART3_SetUartInterruptHandler(UART3_UartInterrupt_ISR);

    // Set the UART3 module to the options selected in the user interface.
    // RXB disabled; 
    U3RXB = 0x0;
    // TXB disabled; 
    U3TXB = 0x0;
    // P1L 0x0; 
    U3P1L = 0x0;
    // P2L 0x0; 
    U3P2L = 0x0;
    // P3L 0x0; 
    U3P3L = 0x0;
    // MODE Asynchronous 8-bit mode; RXEN disabled; TXEN enabled; ABDEN disabled; BRGS normal speed; 
    U3CON0 = 0x20;
    // SENDB disabled; BRKOVR disabled; RXBIMD Set RXBKIF on rising RX input; WUE disabled; ON enabled; 
    U3CON1 = 0x80;
    // FLO off; TXPOL not inverted; STP Transmit 1Stop bit, receiver verifies first Stop bit; RXPOL not inverted; RUNOVF RX input shifter stops all activity; 
    U3CON2 = 0x0;
    // BRGL 25; 
    U3BRGL = 0x19;
    // BRGH 0; 
    U3BRGH = 0x0;
    // STPMD in middle of first Stop bit; TXWRE No error; 
    U3FIFO = 0x0;
    // ABDIE disabled; ABDIF Auto-baud not enabled or not complete; WUIF WUE not enabled by software; 
    U3UIR = 0x0;
    // TXCIF 0x0; RXFOIF not overflowed; RXBKIF No Break detected; CERIF No Checksum error; ABDOVF Not overflowed; 
    U3ERRIR = 0x0;
    // TXCIE disabled; RXFOIE disabled; RXBKIE disabled; FERIE disabled; CERIE disabled; ABDOVE disabled; PERIE disabled; TXMTIE disabled; 
    U3ERRIE = 0x0;

    UART3_SetFramingErrorHandler(UART3_DefaultFramingErrorHandler);
    UART3_SetOverrunErrorHandler(UART3_DefaultOverrunErrorHandler);
    UART3_SetErrorHandler(UART3_DefaultErrorHandler);

    uart3RxLastError.status = 0;

}

bool UART3_IsRxReady(void)
{
    return (bool)(PIR9bits.U3RXIF);
}

bool UART3_is_rx_ready(void)
{    
    return UART3_IsRxReady();
}

bool UART3_IsTxReady(void)
{
    return (bool)(PIR9bits.U3TXIF && U3CON0bits.TXEN);
}

bool UART3_is_tx_ready(void)
{
    return UART3_IsTxReady();
}

bool UART3_IsTxDone(void)
{
    return U3ERRIRbits.TXMTIF;
}

bool UART3_is_tx_done(void)
{
    return UART3_IsTxDone();
}

uart3_status_t UART3_GetLastStatus(void){
    return uart3RxLastError;
}

uart3_status_t UART3_get_last_status(void){
    return UART3_GetLastStatus();
}


uint8_t UART3_Read(void)
{
    while(!PIR9bits.U3RXIF)
    {
    }

    uart3RxLastError.status = 0;

    if(U3ERRIRbits.FERIF){
        uart3RxLastError.ferr = 1;
        UART3_FramingErrorHandler();
    }

    if(U3ERRIRbits.RXFOIF){
        uart3RxLastError.oerr = 1;
        UART3_OverrunErrorHandler();
    }

    if(uart3RxLastError.status){
        UART3_ErrorHandler();
    }

    return U3RXB;
}

void UART3_Write(uint8_t txData)
{
    while(0 == PIR9bits.U3TXIF)
    {
    }

    U3TXB = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return UART3_Read();
}

void putch(char txData)
{
    UART3_Write(txData);
}

void UART3_Transmit_ISR(void)
{
    // use this default transmit interrupt handler code
    if(sizeof(uart3TxBuffer) > uart3TxBufferRemaining)
    {
        U3TXB = uart3TxBuffer[uart3TxTail++];
       if(sizeof(uart3TxBuffer) <= uart3TxTail)
        {
            uart3TxTail = 0;
        }
        uart3TxBufferRemaining++;
    }
    else
    {
        PIE9bits.U3TXIE = 0;
    }
    
    // or set custom function using UART3_SetTxInterruptHandler()
}

void UART3_Receive_ISR(void)
{
    // use this default receive interrupt handler code
    uart3RxStatusBuffer[uart3RxHead].status = 0;

    if(U3ERRIRbits.FERIF){
        uart3RxStatusBuffer[uart3RxHead].ferr = 1;
        UART3_FramingErrorHandler();
    }
    
    if(U3ERRIRbits.RXFOIF){
        uart3RxStatusBuffer[uart3RxHead].oerr = 1;
        UART3_OverrunErrorHandler();
    }
    
    if(uart3RxStatusBuffer[uart3RxHead].status){
        UART3_ErrorHandler();
    } else {
        UART3_RxDataHandler();
    }

    // or set custom function using UART3_SetRxInterruptHandler()
}

void UART3_RxDataHandler(void){
    // use this default receive interrupt handler code
    uart3RxBuffer[uart3RxHead++] = U3RXB;
    if(sizeof(uart3RxBuffer) <= uart3RxHead)
    {
        uart3RxHead = 0;
    }
    uart3RxCount++;
}

void UART3_DefaultFramingErrorHandler(void){}

void UART3_DefaultOverrunErrorHandler(void){}

void UART3_DefaultErrorHandler(void){
}

void UART3_SetFramingErrorHandler(void (* interruptHandler)(void)){
    UART3_FramingErrorHandler = interruptHandler;
}

void UART3_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    UART3_OverrunErrorHandler = interruptHandler;
}

void UART3_SetErrorHandler(void (* interruptHandler)(void)){
    UART3_ErrorHandler = interruptHandler;
}

void UART3_FramingError_ISR(void)
{
    // To clear the interrupt condition, all bits in the UxERRIR register must be cleared
    U3ERRIR = 0;
    
    // add your UART3 error interrupt custom code

}

void UART3_UartInterrupt_ISR(void)
{
    // WUIF must be cleared by software to clear UxIF
    U3UIRbits.WUIF = 0;
    
    // add your UART3 interrupt custom code
}

void UART3_SetRxInterruptHandler(void (* InterruptHandler)(void)){
    UART3_RxInterruptHandler = InterruptHandler;
}

void UART3_SetTxInterruptHandler(void (* InterruptHandler)(void)){
    UART3_TxInterruptHandler = InterruptHandler;
}

void UART3_SetFramingErrorInterruptHandler(void (* InterruptHandler)(void)){
    UART3_FramingErrorInterruptHandler = InterruptHandler;
}

void UART3_SetUartInterruptHandler(void (* InterruptHandler)(void)){
    UART3_UARTInterruptHandler = InterruptHandler;
}
/**
  End of File
*/

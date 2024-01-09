 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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
#include "mcc_generated_files/system/system.h"


int16_t Counter = 0;
uint16_t measurement = 0;

int main(void) {
    SYSTEM_Initialize();
    ADPCH = POT; // Set ADC Positive Channel to POT (RA0);
    TMR1_Start(); // Start Timer1 (ADC AutoConversion Trigger);
    

    while (1) {

        // Timer1 Overflow will trigger ADC conversion by setting ADGO in hardware; 

        while (ADCON0bits.ADGO); // Wait here while ADC conversion and calculation is in progress;
        
        TMR1_Stop();  //Manually reloads timer 1 after each conversion
        TMR1IF = 0;
        TMR1_Reload();
        TMR1_Start();
        
        measurement = ADCC_GetFilterValue(); //sets the ADC calculation to a variable
        
        DataStreamer.measurement = measurement; //sends the calculation to data streamer

        DataStreamer.Inverse = -measurement; //sends the negative calculation to the data streamer
        DataStreamer.Counter = Counter; //sends the counter variable to the data streamer
        
        Counter++;
        
        DataStreamer_FrameSend(&DataStreamer,sizeof(DataStreamer)); //Sends the variables in the order they were gathered. 

        while (!ADCON0bits.ADGO); // Wait here until Timer1 triggers ADGO again;
        
    }
}
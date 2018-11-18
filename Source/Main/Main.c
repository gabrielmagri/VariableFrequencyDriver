/*
 * Main.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include"VariableFrequencyManager.h"
#include "../DeviceDrivers/Debug.h"
#include "../DeviceDrivers/UART.h"
#include "../DeviceDrivers/PLL.h"
#include "../DeviceDrivers/ADCSWTrigger.h"
#include "../DeviceDrivers/Nokia5110.h"

volatile unsigned long ADCvalue;
unsigned long volatile delay;

void main(void)
{


    /* Call the manager initialization routine */
    //VariableFrequencyManager_Init();

    //TODO remove this tests for UART0
//    PLL_Init();
//    char _myString[] = {'H', 'e', 'l', 'l', 'o', '\n', '\0'};
//    UART_Init();
//    UART_OutString(_myString);
//    ADC0_InitSWTriggerSeq3_Ch1();
//    Nokia5110_Init();
//    Nokia5110_Clear();
//    Debug_Init();
//    ADC0_InitSWTriggerSeq3_Ch1();

    for(;;)
    {
        /* Run the periodic execution logic */
        VariableFrequencyManager_Run();

        //TODO remove this test codes
//        ADCvalue = ADC0_InSeq3();
//        Nokia5110_SetCursor(0, 0);
//        Nokia5110_OutUDec(ADCvalue);
//        Debug_TooglePin_2();
//        ADCvalue = ADC0_InSeq3();
//        UART_OutUDec(ADCvalue);
//        Debug_TooglePin_2();
//        UART_OutChar('\n');
//        for(delay=0; delay<10000; delay++);


    }

}

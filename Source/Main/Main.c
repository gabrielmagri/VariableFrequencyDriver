/*
 * Main.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include "../DeviceDrivers/PLL.h"
#include "../DeviceDrivers/LEDs.h"
#include "../DeviceDrivers/Nokia5110.h"

void main(void)
{

    PLL_Init();
    LEDs_Init();
    Nokia5110_Init();


    /* Display the Unisinos logo into the whole screen */
    Nokia5110_Clear();
    Nokia5110_PrintBMP(0, 47, _logoUni, 0);
    Nokia5110_DisplayBuffer();

    for(;;)
    {
        LEDs_Blue();
    }

}





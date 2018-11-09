/*
 * DisplayManager.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include "DisplayManager.h"
#include "../DeviceDrivers/Nokia5110.h"

/* ***************DisplayManager_Init******************
 * This function initialize all the device drivers
 * used and needed by this module
 * Input: none
 * Output: none
 */
void DisplayManager_Init(void)
{
    Nokia5110_Init();
}

/* **************displayUnisinosLogo*********************
 * This function clears the whole screen and update it
 * with a full 84x48 bmp UNISINOS logo image
 * Input: none
 * Output: none
 */
void DisplayManager_DisplayUnisinosLogo(void)
{
    Nokia5110_Clear();
    Nokia5110_PrintBMP(0, 47, _logoUni, 0);
    Nokia5110_DisplayBuffer();
}

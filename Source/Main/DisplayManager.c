/*
 * DisplayManager.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include <stdbool.h>

#include "PwmOutputController.h"
#include "DisplayManager.h"
#include "../DeviceDrivers/Nokia5110.h"
#include "../DeviceDrivers/LEDs.h"

////////////////////////////////////////////////////////////////////

/*  */

////////////////////////////////////////////////////////////////////


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

/* ******************DisplayManager_DisplayOperationalInfo*************************
 * This function update the whole display screen with the operational
 * information, like motor status and configured timers.
 * Input: none
 * Output: none */
void DisplayManager_OperationalInfo(MotorState state, unsigned short sFreq, unsigned short aFreq, bool smooth)
{
    Nokia5110_Clear();
    switch(state) {
        case SM_MOTOR_INITIAL:
            Nokia5110_OutString("   INIT    ");
            DisplayManager_UpdateSmoothIndicator(smooth);
        case SM_MOTOR_STARTED:
            Nokia5110_OutString("  STARTED  ");
            DisplayManager_UpdateSmoothIndicator(smooth);
            break;
        case SM_MOTOR_STOPPED:
            Nokia5110_OutString("  STOPPED  ");
            DisplayManager_UpdateSmoothIndicator(smooth);
            break;
        case SM_MOTOR_UPDATING:
            Nokia5110_OutString("  UPDATING ");
            DisplayManager_UpdateSmoothIndicator(smooth);
            break;
        default:
            break;
    }

    Nokia5110_OutString("------------");
    Nokia5110_OutString("Selec. freq:");
    Nokia5110_OutUDec(sFreq);
    Nokia5110_OutString(" Hz    ");
    Nokia5110_OutString("Actual freq:");
    Nokia5110_OutUDec(aFreq);
    Nokia5110_OutString(" Hz    ");

}

/* ******************DisplayManager_UpdatedMotorState*************************
 * This function provides a way to update a specific display position,
 * more precisely, the motor state position. It's update with the new state
 * Input: none
 * Output: none */
void DisplayManager_UpdatedMotorState(MotorState state)
{
    Nokia5110_SetCursor(0, 0);
    switch(state) {
        case SM_MOTOR_STARTED:
            Nokia5110_OutString("  STARTED  ");
            break;
        case SM_MOTOR_STOPPED:
            Nokia5110_OutString("  STOPPED  ");
            break;
        case SM_MOTOR_UPDATING:
            Nokia5110_OutString("  UPDATING ");
            break;
        default:
            break;
    }
}

/* ******************DisplayManager_ConfigInfo*************************
 * This function update the whole display screen with the configuration
 * information, configured timers, current selected time unit, current
 * selected timer to be updated.
 * Input: none
 * Output: none
 */
void DisplayManager_ConfigInfo(void)
{
    Nokia5110_SetCursor(0, 0);
    Nokia5110_OutString("Config MENU:");
    Nokia5110_OutString("------------");

}

/* **************DisplayManager_UpdatedSelectedFrequency*********************
 * This function updates on the screen just the current
 * timers. Can be called after their changes
 * Input: none
 * Output: none
 */
void DisplayManager_UpdateSelectedFrequency(unsigned short freq) {
    Nokia5110_SetCursor(0, 3);
    Nokia5110_OutUDec(freq);
}

/* **************DisplayManager_UpdateActualFrequency*********************
 * This function updates on the screen just the current
 * timers. Can be called after their changes
 * Input: none
 * Output: none
 */
void DisplayManager_UpdateActualFrequency(unsigned short freq) {
    Nokia5110_SetCursor(0, 5);
    Nokia5110_OutUDec(freq);
}

/* **************DisplayManager_UpdateSmoothIndicator*********************
 * This function updates on the screen the smooth update indicator
 * Input: none
 * Output: none
 */
void DisplayManager_UpdateSmoothIndicator(bool smooth) {
    Nokia5110_SetCursor(11, 0);
    if(smooth == true) Nokia5110_OutString("*");
    else if(smooth == false) Nokia5110_OutString(" ");
}


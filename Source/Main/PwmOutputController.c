/*
 * PwmOutputController.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include "../DeviceDrivers/LEDs.h"
#include "PwmOutputController.h"
#include "tm4c123gh6pm.h"

//////////////////////////////////////////////////////////////////////////////
////////////////      LOCAL FUNCTIONS PROTOTYPES    //////////////////////////
//////////////////////////////////////////////////////////////////////////////

/* Initialize the Systick Timer */
void Systick_Init(void);

//////////////////////////////////////////////////////////////////////////////
/////////////////////      GLOBAL VARIABLE    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

unsigned short _motorState    = SM_STOPPED;   // The motor control state initiate as stopped.
unsigned char  _buttonClicked = NONE_CLICKED; // The variable that holds the button events.

//////////////////////////////////////////////////////////////////////////////


/* ***************PwmOuputController_Init******************
 * This function performs the whole initialization needed
 * for this module
 * Input: none
 * Output: none
 */
void PwmOuputController_Init(void)
{
    LEDs_Init();
    //TODO implement the initialization of the pins used in the pwm
    Systick_Init();
}

/* ************Systick_Init*******************
 * Initialize the Systick Timer
 * Input: none
 * Output: none
 */
void Systick_Init(void)
{

    //TODO update if need to initialize a variable based on interrupts

    NVIC_ST_CTRL_R = 0;                           // disable SysTick during setup
    NVIC_ST_RELOAD_R = DEFAULT_RELOAD;            // reload value
    NVIC_ST_CURRENT_R = 0;                        // any write to current clears it
    NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF; // priority 0
    NVIC_ST_CTRL_R = 0x00000007;                  // enable with core clock and interrupts

}

/* ***************PwmOuputController_Start******************
 * Start the motor with the currently configured frequency
 * Only allow to start if the motor is currently stopped
 * Input: none
 * Output: none
 */
void PwmOuputController_Start(void)
{
    /* Only allow to start if the motor is currently stopping or stopped */
    if( _motorState == SM_STOPPED ) {
        /* Signalize the intention to start the motor */
        _buttonClicked = START_CLICKED;
    }
}

/* ***************PwmOuputController_Stop******************
 * Stop the motor
 * Only allow to stop if the motor is currently started
 * Input: none
 * Output: none
 */
void PwmOuputController_Stop(void)
{
    /* Only allow to start if the motor is currently stopping or stopped */
    if( _motorState == SM_STARTED ) {
        /* Signalize the intention to start the motor */
        _buttonClicked = STOP_CLICKED;
    }
}

/* **********PwmOuputController_UpdateFrequency************
 * Update the frequency set to the motor operate
 * Input: freq - The new frequency {unsigned short}
 * Output: none
 */
void PwmOuputController_UpdateFrequency(unsigned short freq)
{
    //TODO implement the update of the frequency
}






















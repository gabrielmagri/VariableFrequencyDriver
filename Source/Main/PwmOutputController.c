/*
 * PwmOutputController.c
 *
 * By the calculations we want a interrupt frequency of 233280 Hz.
 * As the Clock frequency is 80MHz we need a value of (80Mhz/233280 - 1) at NVIC_ST_RELOAD_R.
 * So, the result value for NVIC_ST_RELOAD_R is 341.9355, wich can be rounded to 342.
 *
 * The amount of interrupts that represents the full pwm cycle can be calculated by:
 * 233280/(72 * wf)
 * Where wf is the fundamental frequency that can tour from 30 all the way up to 90
 *
 * With the value of the total interrupts per pwm cycle we can calculate the table of TONs
 * That will be outputed along the sine wave. To calculate it we can do:
 * RoundToNearest(Interrupts per pwm cycle * SinOutTable[i]) = TON[i]
 * Where SinOutTable is a fixed table with 36 values representing the output of:
 * sin(x) with 0 < x <= 180, where x is increased in units of 5 (5, 10, 15 ... 175, 180).
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include "../DeviceDrivers/LEDs.h"
#include "PwmOutputController.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

//////////////////////////////////////////////////////////////////////////////
////////////////      LOCAL FUNCTIONS PROTOTYPES    //////////////////////////
//////////////////////////////////////////////////////////////////////////////

/* Initialize the Systick Timer */
void Systick_Init(void);

/* Initialize the pins use to output the pwm signal */
void PwmPinsInit(void);

/* */
void PwmPinOn(void);

/* */
void PwmPinOff(void);

/* */
void PwmPin2Toogle(void);

/* */
void UpdateTonTable(void);

//////////////////////////////////////////////////////////////////////////////
/////////////////////      GLOBAL VARIABLE    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

MotorState     _motorState    = SM_STOPPED;   // The motor control state initiate as stopped.
unsigned char  _buttonClicked = NONE_CLICKED; // The variable that holds the button events.
unsigned int   _frequency     = 60;           // The variable that holds the fundamental frequency
unsigned int   _interruptsInPwmCycle = 0;     // The variable that represents the amount of cycles that represent a full pwm cycle
unsigned int   _tonTable[36];                 // The table that holds the dynamically calculated ton times
unsigned int   _tonIndex = 0;                 // The current indexes within ton Table
unsigned long  _interruptsCounter = 0;        // The counter of already reached interrupts within motor Started state


//////////////////////////////////////////////////////////////////////////////


/* ***************PwmOuputController_Init******************
 * This function performs the whole initialization needed
 * for this module
 * Input: none
 * Output: none
 */
void PwmOuputController_Init(short freq)
{
    _frequency = freq;
    _interruptsInPwmCycle = INTERRUPT_FREQ / (PWM_CYCLE_WITHIN_FULL_SINE * _frequency);

    UpdateTonTable();

    /* Initialize drivers */
    IntMasterEnable(); // Enable interrupts that are used within this module
    LEDs_Init();
    PwmPinsInit();
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

/* **************PwmPinsInit*********************
 * Initialize the two pwm pins
 * Input: none
 * Output: none
 */
void PwmPinsInit(void)
{
    unsigned long volatile delay;
    SYSCTL_RCGC2_R |= 0x00000002;     // activate port B
    delay = SYSCTL_RCGC2_R;           // execute some delay
    GPIO_PORTB_AMSEL_R &= ~0x03;      // no analog in PB0-1
    GPIO_PORTB_PCTL_R &= ~0x000000FF; // regular function on PB0-1
    GPIO_PORTB_DIR_R |= 0x03;         // make PB0-1 OUT
    //GPIO_PORTB_DR8R_R |= 0x03;        // can drive up to 8mA out
    GPIO_PORTB_AFSEL_R &= ~0x03;      // disable alt funct on PB0-1
    GPIO_PORTB_DEN_R |= 0x03;         // enable digital I/O on PB0-1
}

/* **************UpdateTonTable*********************
 * Update the table of Tons based on already calculated values
 * Input: none
 * Output: none
 */
void UpdateTonTable(void)
{
    int i=0;
    for(i=0; i<36; i++)
    {
        //TODO improve comments
        /*  */
        _tonTable[i] = (int)((double)(_interruptsInPwmCycle * _SinOutTable[i]) + 0.5);
    }
}

/* */
void PwmPinOn(void)
{
    GPIO_PORTB_DATA_R |= 0x01;
}

/* */
void PwmPinOff(void)
{
    GPIO_PORTB_DATA_R &= ~0x01;
}

/* **************PwmPin2Toogle*********************
 * Toogle one pin of the pwm pins
 * Input: none
 * Output: none
 */
void PwmPin2Toogle(void)
{
    GPIO_PORTB_DATA_R =  (GPIO_PORTB_DATA_R ^ 0x02);
}

/* ***************PwmOuputController_Start******************
 * Start the motor with the currently configured frequency
 * Only allow to start if the motor is currently stopped
 * Input: none
 * Output: none
 */
void PwmOuputController_Start(void)
{
    /* Only allow to start if the motor is currently stopped */
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

void SysTick_Handler(void)
{

    PwmPin2Toogle();

    // ------------------------------------------------------------------
    // Check for button clicks notified by any caller.
    // ------------------------------------------------------------------
    switch(_buttonClicked)
    {
        case START_CLICKED:
            _motorState = SM_START_REQUIRED;
            _buttonClicked = NONE_CLICKED; // Clear the click
            break;
        case STOP_CLICKED:
            _motorState = SM_STOP_REQUIRED;
            _buttonClicked = NONE_CLICKED; // Clear the click
            break;
        case NONE_CLICKED:
            break;
        default:
            break;
    }

    switch(_motorState)
    {
        case SM_START_REQUIRED:
//            if( _tonTable[_tonIndex] != 0)
//            {
//                PwmPinOn();
//            }
            _motorState = SM_STARTED;
            break;

        case SM_STOP_REQUIRED:

            PwmPinOff();
            _motorState = SM_STOPPED;
            break;

        case SM_STARTED:

            /* If reached the cycles values for ton must make proceed to toff */
            if( (_interruptsCounter + 1) == _tonTable[_tonIndex] )
            {
                PwmPinOff();
                _interruptsCounter++;
            }
            else if( (_interruptsCounter + 1) == _interruptsInPwmCycle )
            {
                PwmPinOn();
                if(_tonIndex < 35)
                {
                    _tonIndex++;
                }
                else
                {
                    _tonIndex = 0;
                }
                _interruptsCounter = 0;

            } else {
                _interruptsCounter++;
            }
            break;

        case SM_STOPPED:

            break;

        case SM_SLEEP:

            LEDs_Blue();

            _interruptsCounter++;
            if(_interruptsCounter >= 36)
            {
                _interruptsCounter = 0;
                _motorState = SM_STARTED;
            }

            break;

        default:
            break;
    }

}




















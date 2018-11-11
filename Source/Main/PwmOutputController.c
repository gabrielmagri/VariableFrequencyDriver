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

/* Make the current selected pwm pin HI {1} */
void PwmPinOn(void);

/* Make the current selected pwm pin LOW {0} */
void PwmPinOff(void);

/* Toogle the pin within every Systick Interrupt, used for debug */
void InterruptPinToogle(void);

/* Recalculate the entire ton table base on the current setted frequency */
void UpdateTonTable(void);

/* Evaluate if it was required to start the motor */
bool CheckForStartRequired(void);

/* Evaluate if it was required to stop the motor */
bool CheckForStopRequired(void);

/* Update the current index within the ton table */
void UpdateIndex(void);

//////////////////////////////////////////////////////////////////////////////
/////////////////////      GLOBAL VARIABLE    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

MotorState     _motorState    = SM_STOPPED;   // The motor control state initiate as stopped.
PwmPin         _pwmPin        = PWM_PIN_HI;   // The pin that is currently selected for output.
ButtonState    _buttonClicked = NONE_CLICKED; // The variable that holds the button events.
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
void PwmOuputController_Init(unsigned short freq)
{

    /* Calls the function that update the sine frequency */
    PwmOuputController_UpdateFrequency(freq);

    /* Initialize drivers */
    IntMasterEnable(); // Enable interrupts that are used within this module
    LEDs_Init();       // Initialize the LEDs driver
    PwmPinsInit();     // Initialize the Driver for the pwm pins
    Systick_Init();    // Initilize the Systick Interrupt
}

/* ************Systick_Init*******************
 * Initialize the Systick Timer
 * Input: none
 * Output: none
 */
void Systick_Init(void)
{

    NVIC_ST_CTRL_R = 0;                           // disable SysTick during setup
    NVIC_ST_RELOAD_R = DEFAULT_RELOAD;            // reload value
    NVIC_ST_CURRENT_R = 0;                        // any write to current clears it
    NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF; // priority 0
    NVIC_ST_CTRL_R = 0x00000007;                  // enable with core clock and interrupts

}

/* **************PwmPinsInit*********************
 * Initialize the two pwm pins and the debug pin
 * Input: none
 * Output: none
 */
void PwmPinsInit(void)
{
    unsigned long volatile delay;
    SYSCTL_RCGC2_R |= 0x00000002;     // activate port B
    delay = SYSCTL_RCGC2_R;           // execute some delay
    GPIO_PORTB_AMSEL_R &= ~0x07;      // no analog in PB0-2
    GPIO_PORTB_PCTL_R &= ~0x00000FFF; // regular function on PB0-2
    GPIO_PORTB_DIR_R |= 0x07;         // make PB0-2 OUT
    //GPIO_PORTB_DR8R_R |= 0x07;      // can drive up to 8mA out
    GPIO_PORTB_AFSEL_R &= ~0x07;      // disable alt funct on PB0-2
    GPIO_PORTB_DEN_R |= 0x07;         // enable digital I/O on PB0-2
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
        /* As both sine wave semicycles are equivalent we calculate and output base on one semicycle, wich leads to 36 points.
         * We first multiply the position of the sine wave table for the already calculated amount of interruts within one (1/36) pwm cycle
         * The result of it is a double value that corresponds to the total pwm cycles that we need to stay in HI.
         * By adding +0.5 and casting to int we are executing a "round to the nearest" with the ton value */
        _tonTable[i] = (int)((double)(_interruptsInPwmCycle * _SinOutTable[i]) + 0.5);
    }
}

/* ***********************PwmPinOn***********************
 * Make the current selected pwm pin HI {1}
 * Input: none
 * Output: none
 */
void PwmPinOn(void)
{
    if(_pwmPin == PWM_PIN_HI) GPIO_PORTB_DATA_R |= 0x01;
    if(_pwmPin == PWM_PIN_LOW) GPIO_PORTB_DATA_R |= 0x02;
}

/* ***********************PwmPinOff***********************
 * Make the current selected pwm pin LOW {0}
 * Input: none
 * Output: none
 */
void PwmPinOff(void)
{
    if(_pwmPin == PWM_PIN_HI) GPIO_PORTB_DATA_R &= ~0x01;
    if(_pwmPin == PWM_PIN_LOW) GPIO_PORTB_DATA_R &= ~0x02;
}

/* **************InterruptPinToogle*********************
 * Toogle the pin within every Systick Interrupt, used for debug
 * Input: none
 * Output: none
 */
void InterruptPinToogle(void)
{
    GPIO_PORTB_DATA_R =  (GPIO_PORTB_DATA_R ^ 0x04);
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
    if( _motorState == SM_STOPPED )
    {
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
    if( _motorState == SM_STARTED )
    {
        /* Signalize the intention to start the motor */
        _buttonClicked = STOP_CLICKED;
    }
}

/* ***************CheckForStartRequired******************
 * Evaluate if it was required to start the motor
 * Input: none
 * Output: bool
 */
bool CheckForStartRequired(void)
{
    return (_buttonClicked == START_CLICKED);
}

/* ***************CheckForStopRequired******************
 * Evaluate if it was required to stop the motor
 * Input: none
 * Output: bool
 */
bool CheckForStopRequired(void)
{
    return (_buttonClicked == STOP_CLICKED);
}

/* ***************CheckForStopRequired******************
 * Update the current index within the ton table;
 * Toogle the current selected pwm pin;
 * Reset the interrupts counter;
 * Input: none
 * Output: none
 */
void UpdateIndex(void)
{
    if(_tonIndex < 35)
    {
       _tonIndex++;
    }
    else
    {
       if(_pwmPin == PWM_PIN_HI) _pwmPin = PWM_PIN_LOW;
       else if(_pwmPin == PWM_PIN_LOW) _pwmPin = PWM_PIN_HI;
       _tonIndex = 0;
    }
    _interruptsCounter = 0;
}

/* **********PwmOuputController_UpdateFrequency************
 * Update the frequency set to the motor operate
 * Input: freq - The new frequency {unsigned short}
 * Output: none
 */
void PwmOuputController_UpdateFrequency(unsigned short freq)
{
    /* Update the setted frequency */
    _frequency = freq;

    /* Calculate the total interrupts units that compose the full pwm cycle */
    _interruptsInPwmCycle = INTERRUPT_FREQ / (PWM_CYCLE_WITHIN_FULL_SINE * _frequency);

    UpdateTonTable();
}

/* This is the ISR (Interrupt Service Routin) that handle the Systick Interrupts
 * The ISR is responsible mainly for the output of the pwm pins, based on the frequency
 *  and the motor state, and for updating the LEDs that sinalize the motor state to the user. */
void SysTick_Handler(void)
{

    InterruptPinToogle();

    /* Unique motor state machine routine */
    switch(_motorState)
    {

        case SM_STOPPED:

            LEDs_None();

            if(CheckForStartRequired())
            {
                _motorState = SM_STARTED;
                _interruptsCounter = 0;
                _tonIndex = 0;
            }

            break;

        case SM_STARTED:

            if(CheckForStopRequired())
            {
                PwmPinOff();
            }
            else
            {

                /* Must verify that there is at least one cycle in ton at the first cycle*/
                if( ( _interruptsCounter == 0 ) && ( _tonTable[_tonIndex] != 0 ) )
                {
                    PwmPinOn();
                }

                /* If reached the cycles values for ton and it's also the total number of pwm cycles
                 * The function shall execute the pwm pin off, the resets and the pwm selected pin toogle
                 * */
                else if( ( _interruptsCounter == _tonTable[_tonIndex] ) && ( _interruptsCounter == _interruptsInPwmCycle ) )
                {
                    PwmPinOff();
                    UpdateIndex();
                    break;
                }

                /* If reached the cycles values for ton must make the pin off */
                else if( _interruptsCounter == _tonTable[_tonIndex] )
                {
                    PwmPinOff();
                }

                /* If reached the total number of pwm cycles, the function shall execute
                 *  the resets and the pwm selected pin toogle.
                 * */
                else if( _interruptsCounter == _interruptsInPwmCycle )
                {
                    UpdateIndex();
                    break;
                }

                _interruptsCounter++;

            }

            break;

        default:
            break;
    }

}

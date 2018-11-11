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

/* */
bool CheckForStartRequired(void);

/* */
bool CheckForStopRequired(void);

/* */
void UpdateIndex(void);

//////////////////////////////////////////////////////////////////////////////
/////////////////////      GLOBAL VARIABLE    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

MotorState     _motorState    = SM_STOPPED;   // The motor control state initiate as stopped.
PwmPin         _pwmPin        = PWM_PIN_HI;   // The pin that is currently selected for output.
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
void PwmOuputController_Init(unsigned short freq)
{

    PwmOuputController_UpdateFrequency(freq);

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
        //TODO improve comments
        /*  */
        _tonTable[i] = (int)((double)(_interruptsInPwmCycle * _SinOutTable[i]) + 0.5);
    }
}

/* */
void PwmPinOn(void)
{
    if(_pwmPin == PWM_PIN_HI) GPIO_PORTB_DATA_R |= 0x01;
    if(_pwmPin == PWM_PIN_LOW) GPIO_PORTB_DATA_R |= 0x02;
}

/* */
void PwmPinOff(void)
{
    if(_pwmPin == PWM_PIN_HI) GPIO_PORTB_DATA_R &= ~0x01;
    if(_pwmPin == PWM_PIN_LOW) GPIO_PORTB_DATA_R &= ~0x02;
}

/* **************PwmPin2Toogle*********************
 * Toogle one pin of the pwm pins
 * Input: none
 * Output: none
 */
void PwmPin2Toogle(void)
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

bool CheckForStartRequired(void)
{
    return (_buttonClicked == START_CLICKED);
}

/* */
bool CheckForStopRequired(void)
{
    return (_buttonClicked == STOP_CLICKED);
}

/**/
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
    _frequency = freq;
    _interruptsInPwmCycle = INTERRUPT_FREQ / (PWM_CYCLE_WITHIN_FULL_SINE * _frequency);

    UpdateTonTable();
}

void SysTick_Handler(void)
{

    PwmPin2Toogle();

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
                 * The function shall execute the clean up and the index increment
                 * */
                else if( ( _interruptsCounter == _tonTable[_tonIndex] ) && ( _interruptsCounter == _interruptsInPwmCycle ) )
                {
                    PwmPinOff();
                    UpdateIndex();
                    break;
                }

                /* If reached the cycles values for ton must make proceed to toff */
                else if( _interruptsCounter == _tonTable[_tonIndex] )
                {
                    PwmPinOff();
                }

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




















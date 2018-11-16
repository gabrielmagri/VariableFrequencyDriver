/*
 * VariableFrequencyManager.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include "../DeviceDrivers/PLL.h"
#include "../DeviceDrivers/LEDs.h"
#include "../DeviceDrivers/Keyboard.h"
#include "VariableFrequencyManager.h"
#include "PwmOutputController.h"
#include "DisplayManager.h"
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////
////////////////      LOCAL FUNCTIONS PROTOTYPES    //////////////////////////
//////////////////////////////////////////////////////////////////////////////

/* Execute the initialize routine  */
void InitializeRoutine(void);

/* Execute the normal routine  */
void NormalRoutine(void);

/* Execute the configuration routine */
void ConfigRoutine(void);

/* Update smoothly the sine wave natural frequency */
void UpdateRoutine(void);

/*  */
void checkBounds(void);

//////////////////////////////////////////////////////////////////////////////
/////////////////////      GLOBAL VARIABLE    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

static StateMachine _state = SM_INITIALIZING;
/* The last motor status remembered */
static MotorState _lastMotorStatus = SM_MOTOR_INITIAL;
/* The select and configurable fundamental frequency to the sine wave*/
static unsigned short _selectedFrequency = 60;
/* The current fundamental frequency to the sine wave used to generate smooth updates*/
static unsigned short _actualFrequency = 0;
/* Flag that enable the smooth update between two different frequencies */
static bool _smoothUpdateEnabled = true;

//////////////////////////////////////////////////////////////////////////////


/* ********VariableFrequencyManager_Init**********
 * This function initialize all the device drivers
 * used and needed by this module
 * Input: none
 * Output: none
 */
void VariableFrequencyManager_Init(void)
{
    PLL_Init();
    LEDs_Init();
    Keyboard_Init();
    PwmOuputController_Init(_actualFrequency);
    DisplayManager_Init();

    /* Display the Unisinos logo into the whole screen */
    DisplayManager_DisplayUnisinosLogo();

}

/* ********VariableFrequencyManager_Run**********
 * This function execute the full logic once
 * Input: none
 * Output: none
 */
void VariableFrequencyManager_Run(void)
{
    switch(_state)
    {
        case SM_INITIALIZING:
            InitializeRoutine();
            break;
        case SM_NORMAL:
            NormalRoutine();
            break;
        case SM_CONFIGURING:
            ConfigRoutine();
            break;
        case SM_UPDATING:
            UpdateRoutine();
            break;
        default:
            break;
    }
}


/* Execute the initialize routine  */
void InitializeRoutine(void)
{
    DisplayManager_OperationalInfo(_lastMotorStatus, _selectedFrequency, _actualFrequency, _smoothUpdateEnabled);
    _state = SM_NORMAL;
}

/* Execute the normal routine  */
void NormalRoutine(void)
{

    MotorState tempMotorStatus = Control_GetMotorState();
    if(_lastMotorStatus != tempMotorStatus) {
        _lastMotorStatus = tempMotorStatus;
        if(tempMotorStatus == SM_MOTOR_STARTED) LEDs_Red();
        else if(tempMotorStatus == SM_MOTOR_STOPPED) LEDs_Green();
        DisplayManager_UpdatedMotorState(tempMotorStatus);
    }



    switch(Keyboard_In()) {
        case KEY_ONE:
            PwmOuputController_Start();
            _lastMotorStatus = SM_MOTOR_UPDATING;
            DisplayManager_UpdatedMotorState(_lastMotorStatus);
            _state = SM_UPDATING;
            LEDs_Blue();
            break;
        case KEY_TWO:
            PwmOuputController_Stop();
            _actualFrequency = 0;
            DisplayManager_UpdateActualFrequency(_actualFrequency);
            PwmOuputController_UpdateFrequency(_actualFrequency);
            break;
        case KEY_THREE:
            DisplayManager_ConfigInfo(); // Display on screen all the configuration information
            _state = SM_CONFIGURING; // Change the state to configuration state
            break;
        case KEY_FOUR:
            if(_smoothUpdateEnabled == true) _smoothUpdateEnabled = false;
            else if(_smoothUpdateEnabled == false) _smoothUpdateEnabled = true;
            DisplayManager_UpdateSmoothIndicator(_smoothUpdateEnabled);
            break;
        default:
            break;
    }

}

/* Execute the configuration routine */
void ConfigRoutine(void)
{
    switch(Keyboard_In()) {
        case KEY_THREE:
            DisplayManager_OperationalInfo(_lastMotorStatus, _selectedFrequency, _actualFrequency, _smoothUpdateEnabled);
            _state = SM_NORMAL;
            break;
        default:
            break;
    }

    switch(Keyboard_Continuous_In()) {
        case KEY_ONE:
            _selectedFrequency++;
            checkBounds();
            DisplayManager_UpdateSelectedFrequency(_selectedFrequency);
            break;

        case KEY_TWO:
            _selectedFrequency--;
            checkBounds();
            DisplayManager_UpdateSelectedFrequency(_selectedFrequency); //Update the screen after changing the value
            break;

        default:
            break;
    }

}

/* Update smoothly the sine wave natural frequency */
void UpdateRoutine(void)
{

    int i = 0, j=0;
    short deltaFreq = _selectedFrequency - _actualFrequency;

    if(_smoothUpdateEnabled == true)
    {
        if(deltaFreq > 0)
        {
            for (i = 0; i < deltaFreq; i++) {
                if(Keyboard_InNoDebounce() == KEY_TWO)
                {
                    PwmOuputController_Stop();
                    _actualFrequency = 0;
                    DisplayManager_UpdateActualFrequency(_actualFrequency);
                    PwmOuputController_UpdateFrequency(_actualFrequency);
                    break;
                }
                else
                {
                    _actualFrequency++;
                    DisplayManager_UpdateActualFrequency(_actualFrequency);
                    PwmOuputController_UpdateFrequency(_actualFrequency);
                    for (j = 0; j < 500000; ++j);
                }

            }
        }
        else
        {
            for (i = 0; i > deltaFreq; i--) {
                if(Keyboard_InNoDebounce() == KEY_TWO)
                {
                    PwmOuputController_Stop();
                    _actualFrequency = 0;
                    DisplayManager_UpdateActualFrequency(_actualFrequency);
                    PwmOuputController_UpdateFrequency(_actualFrequency);
                    break;
                }
                else
                {
                    _actualFrequency--;
                    DisplayManager_UpdateActualFrequency(_actualFrequency);
                    PwmOuputController_UpdateFrequency(_actualFrequency);
                    for (j = 0; j < 500000; ++j);
                }

            }
        }
    }
    else
    {
        _actualFrequency = _selectedFrequency;
        DisplayManager_UpdateActualFrequency(_actualFrequency);
        PwmOuputController_UpdateFrequency(_actualFrequency);
    }

    _state = SM_NORMAL;

}

/* **************checkBounds*********************
 * This functions checks and update the current
 * timers values, according to their relations
 * with the specified bounds for them.
 * Input: none
 * Output: none
 */
void checkBounds(void) {
    if(_selectedFrequency > UPPER_BOUND) {
        _selectedFrequency = UPPER_BOUND;
    } else if(_selectedFrequency < LOWER_BOUND) {
        _selectedFrequency = LOWER_BOUND;
    }
}



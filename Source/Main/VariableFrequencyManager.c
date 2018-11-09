/*
 * VariableFrequencyManager.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include "../DeviceDrivers/PLL.h"
#include "../DeviceDrivers/LEDs.h"
#include "VariableFrequencyManager.h"
#include "DisplayManager.h"

//////////////////////////////////////////////////////////////////////////////
////////////////      LOCAL FUNCTIONS PROTOTYPES    //////////////////////////
//////////////////////////////////////////////////////////////////////////////

/* Execute the normal toutine  */
void NormalRoutine(void);

/* Execute the configuration routine */
void ConfigRoutine(void);

//////////////////////////////////////////////////////////////////////////////
/////////////////////      GLOBAL VARIABLE    ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

unsigned short _state = SM_INITIALIZING;

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
        case SM_NORMAL:
            NormalRoutine();
            break;
        case SM_CONFIGURING:
            ConfigRoutine();
            break;
        default:
            break;
    }
}


















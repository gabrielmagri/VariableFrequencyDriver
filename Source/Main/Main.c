/*
 * Main.c
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#include"VariableFrequencyManager.h"

void main(void)
{

    /* Call the manager initialization routine */
    VariableFrequencyManager_Init();

    for(;;)
    {
        /* Run the periodic execution logic */
        VariableFrequencyManager_Run();
    }

}

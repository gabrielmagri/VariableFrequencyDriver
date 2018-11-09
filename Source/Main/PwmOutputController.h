/*
 * PwmOutputController.h
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#ifndef SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_
#define SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_

#define NONE_CLICKED  0
#define START_CLICKED 1
#define STOP_CLICKED  2

#define SM_STARTED  0
#define SM_STOPPED  1

//TODO update the bellow item
#define DEFAULT_RELOAD 1

/* ***************PwmOuputController_Init******************
 * This function performs the whole initialization needed
 * for this module
 * Input: none
 * Output: none
 */
void PwmOuputController_Init(void);

/* ***************PwmOuputController_Start******************
 * Start the motor with the currently configured frequency
 * Input: none
 * Output: none
 */
void PwmOuputController_Start(void);

/* ***************PwmOuputController_Stop******************
 * Stop the motor
 * Input: none
 * Output: none
 */
void PwmOuputController_Stop(void);

/* **********PwmOuputController_UpdateFrequency************
 * Update the frequency set to the motor operate
 * Input: freq - The new frequency {unsigned short}
 * Output: none
 */
void PwmOuputController_UpdateFrequency(unsigned short freq);

#endif /* SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_ */

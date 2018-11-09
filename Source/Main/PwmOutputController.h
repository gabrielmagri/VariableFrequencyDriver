/*
 * PwmOutputController.h
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#ifndef SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_
#define SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_

static const double _SinOutTable[] ={
    0.087155743 ,0.173648178 ,0.258819045 ,0.342020143 ,0.422618262 ,0.5 ,0.573576436 ,0.64278761 ,0.707106781 ,
    0.766044443 ,0.819152044 ,0.866025404 ,0.906307787 ,0.939692621 ,0.965925826 ,0.984807753 ,0.996194698 ,1 ,
    0.996194698 ,0.984807753 ,0.965925826 ,0.939692621 ,0.906307787 ,0.866025404 ,0.819152044 ,0.766044443 ,
    0.707106781 ,0.64278761 ,0.573576436 ,0.5 ,0.422618262 ,0.342020143 ,0.258819045 ,0.173648178 ,0.087155743 ,0
};



#define NONE_CLICKED  0
#define START_CLICKED 1
#define STOP_CLICKED  2

typedef enum {SM_STARTED, SM_STOPPED, SM_START_REQUIRED, SM_STOP_REQUIRED, SM_SLEEP} MotorState;

//#define SM_STARTED        0
//#define SM_STOPPED        1
//#define SM_START_REQUIRED 2
//#define SM_STOP_REQUIRED  3
///* Just for debug */
//#define SM_SLEEP  4

/* Default reload value based on the calculations and explained into the .c file */
#define DEFAULT_RELOAD 342
/*  */
#define INTERRUPT_FREQ 233280
/*  */
#define PWM_CYCLE_WITHIN_FULL_SINE 72

/* ***************PwmOuputController_Init******************
 * This function performs the whole initialization needed
 * for this module
 * Input: freq - The fundamental frequency {Hz}
 * Output: none
 */
void PwmOuputController_Init(short freq);

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

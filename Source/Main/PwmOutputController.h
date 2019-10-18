/*
 * PwmOutputController.h
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#ifndef SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_
#define SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_

/* The table that represents all the 36 values from 0 to 180 degrees from 5 by 5;
 * The table is used to calculate how many cycles represent the current ton time
 *  assuming 1 as being all the 36 pwm cycles and 0 as being none. */
static const double _SinOutTable[] ={
    0.087155743 ,0.173648178 ,0.258819045 ,0.342020143 ,0.422618262 ,0.5 ,0.573576436 ,0.64278761 ,0.707106781 ,
    0.766044443 ,0.819152044 ,0.866025404 ,0.906307787 ,0.939692621 ,0.965925826 ,0.984807753 ,0.996194698 ,1 ,
    0.996194698 ,0.984807753 ,0.965925826 ,0.939692621 ,0.906307787 ,0.866025404 ,0.819152044 ,0.766044443 ,
    0.707106781 ,0.64278761 ,0.573576436 ,0.5 ,0.422618262 ,0.342020143 ,0.258819045 ,0.173648178 ,0.087155743 ,0
};

/* All the possible states for the button entry represents the intent to start/stop the motor */
typedef enum {NONE_CLICKED, START_CLICKED, STOP_CLICKED} ButtonState;
/* All the values that the motor state machine can assume */
typedef enum {SM_MOTOR_INITIAL, SM_MOTOR_UPDATING, SM_MOTOR_STARTED, SM_MOTOR_STOPPED} MotorState;
/* The enumeration values that allow to select all the available pwm pins */
typedef enum {PWM_PIN_HI, PWM_PIN_LOW, PWM_PIN_DEBUG} PwmPin;
/* The possible enumeration values for state of the preTonTable */
typedef enum {UPDATED, CONSUMED} TableState;

/* A struct that allows to save the current state of the ton Table that is dynamically calculated */
typedef struct
{
    unsigned int preTonTable[36];
    TableState tState;
} TonTable;

/* Default reload value based on the calculations and explained into the .c file */
#define DEFAULT_RELOAD 342
/* The Systick Interrupts frequency, used for futher calculations */
#define INTERRUPT_FREQ 233280
/* The desired number of pwm cycles within the full sine wave, used for futher calculations */
#define PWM_CYCLE_WITHIN_FULL_SINE 72


/* ***************PwmOuputController_Init******************
 * This function performs the whole initialization needed
 * for this module
 * Input: freq - The fundamental frequency {unsigned short} {Hz}
 * Output: none
 */
void PwmOuputController_Init(unsigned short freq);

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
 * Input: freq - The new frequency {unsigned short} {Hz}
 * Output: none
 */
void PwmOuputController_UpdateFrequency(unsigned short freq);

unsigned int PwmOuputController_GetCurrentTon(void);

/* ************PwmOuputController_GetMotorState*******************
 * Returns the current motor state
 * Input: none
 * Output: MotorState - the motor state
 */
MotorState Control_GetMotorState(void);

#endif /* SOURCE_MAIN_PWMOUTPUTCONTROLLER_H_ */

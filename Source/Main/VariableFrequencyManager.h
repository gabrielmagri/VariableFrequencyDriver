/*
 * VariableFrequencyManager.h
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#ifndef SOURCE_MAIN_VARIABLEFREQUENCYMANAGER_H_
#define SOURCE_MAIN_VARIABLEFREQUENCYMANAGER_H_

#define SM_NORMAL      0
#define SM_CONFIGURING 1
//TODO remove, just for debug
#define SM_WAIT 2

/* ********VariableFrequencyManager_Init**********
 * This function initialize all the device drivers
 * used and needed by this module
 * Input: none
 * Output: none
 */
void VariableFrequencyManager_Init(void);

/* ********VariableFrequencyManager_Run**********
 * This function execute the full logic once
 * Input: none
 * Output: none
 */
void VariableFrequencyManager_Run(void);

#endif /* SOURCE_MAIN_VARIABLEFREQUENCYMANAGER_H_ */

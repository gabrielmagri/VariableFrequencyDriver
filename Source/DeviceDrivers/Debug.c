/*
 * Debug.c
 *
 *  Created on: 17 de nov de 2018
 *      Author: GMAGRI
 */

#include "tm4c123gh6pm.h"
#include "Debug.h"

/* ***************Debug_Init******************
 * This function performs the pins initialization
 * Input: none
 * Output: none
 */
void Debug_Init(void)
{
    unsigned long volatile delay;
    SYSCTL_RCGC2_R |= 0x00000002;     // activate port B
    delay = SYSCTL_RCGC2_R;           // execute some delay
    GPIO_PORTB_AMSEL_R &= ~0x0C;      // no analog in PB2-3
    GPIO_PORTB_PCTL_R &= ~0x0000FF00; // regular function on PB2-3
    GPIO_PORTB_DIR_R |= 0x0C;         // make PB2-3 OUT
    //GPIO_PORTB_DR8R_R |= 0x0C;      // can drive up to 8mA out
    GPIO_PORTB_AFSEL_R &= ~0x0C;      // disable alt funct on PB2-3
    GPIO_PORTB_DEN_R |= 0x0C;         // enable digital I/O on PB2-3
}


void Debug_TooglePin_1(void)
{
    GPIO_PORTB_DATA_R =  (GPIO_PORTB_DATA_R ^ 0x04);
}

void Debug_TooglePin_2(void)
{
    GPIO_PORTB_DATA_R =  (GPIO_PORTB_DATA_R ^ 0x08);
}

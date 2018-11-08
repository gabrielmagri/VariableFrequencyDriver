// LEDs.c
// Runs on TM4C123, 
// Unisinos TGA Eletrônica 4 
// Provide functions for signaling the motor state
// Gabriel Magri, Jaqueline Isabel Prass, Marcos Spellmeier
// September 20, 2018

#include "LEDs.h"
#include "tm4c123gh6pm.h"

// **************LEDs_Init*********************
// Initialize LEDs features
// Input: none
// Output: none
void LEDs_Init(void) {
    unsigned long volatile delay;
	SYSCTL_RCGC2_R |= 0x00000020;   // activate port F
	delay = SYSCTL_RCGC2_R;         // execute some delay
	GPIO_PORTF_AMSEL_R &= ~0x0E;      // no analog in PF2
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // regular function on PF2
	GPIO_PORTF_DIR_R |= 0x0E;         // make PF2 OUT
	//GPIO_PORTE_DR8R_R |= 0x0E;      // can drive up to 8mA out
	GPIO_PORTF_AFSEL_R &= ~0x0E;      // disable alt funct on PF2
	GPIO_PORTF_DEN_R |= 0x0E;         // enable digital I/O on PF2
	
}

// **************LEDs_None*********************
// Turns all LEDs off
// Input: none 
// Output: none
void LEDs_None(void) {
	GPIO_PORTF_DATA_R &= ~0x0E;
}

// **************LEDs_Green*********************
// Turns all LEDs off and green LED ON
// Input: none 
// Output: none
void LEDs_Green(void) {
    GPIO_PORTF_DATA_R &= ~0x06;
	GPIO_PORTF_DATA_R |= 0x08;
}

// **************LEDs_Red*********************
// Turns all LEDs off and red LED ON
// Input: none 
// Output: none
void LEDs_Red(void) {
	GPIO_PORTF_DATA_R &= ~0x0C;
	GPIO_PORTF_DATA_R |= 0x02;
}

// **************LEDs_Blue*********************
// Turns all LEDs off and blue LED ON
// Input: none 
// Output: none
void LEDs_Blue(void) {
	GPIO_PORTF_DATA_R &= ~0x0A;
	GPIO_PORTF_DATA_R |= 0x04;
}


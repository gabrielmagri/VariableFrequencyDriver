/*
 * Keyboard.h
 * Runs on LM4F120 or TM4C123,
 * Unisinos TGA Eletrônica 4
 * There are four keys in the keyboard
 *
 *  Created on: 18 de set de 2018
 *      Author: Gabriel Magri, Jaqueline Isabel Prass, Marcos Spellmeier
 */

static const unsigned long DEBOUNCE_BOUND = (unsigned long)2000000;

// The current debounce value when reading keys
#define DEBOUNCE_VALUE 10000

// The keys option that can be pressed while in operational state
#define KEY_OP_START_PRESSED 0X01
#define KEY_OP_STOP_PRESSED  0X02
#define KEY_OP_ENTER_CONFIG  0X04
#define KEY_OP_DISPLAY_LOGO  0X08

// The keys option that can be pressed while in config state
#define KEY_CFG_TIME_UP          0X01
#define KEY_CFG_TIME_DOWN        0X02
#define KEY_CFG_CONFIG_OK        0X04
#define KEY_CFG_CHANGE_TIME_UNIT 0X08

// A struct that represents a volicity instance when using continuos keyboard input
struct velocity {
	unsigned long timeToWait;
	unsigned short timesToExecute;
	unsigned short amountOfExecution;
	struct velocity *next;
};
typedef struct velocity st_velocity;

// **************Keyboard_Init*********************
// Initialize keyboard key inputs
// Input: none
// Output: none
void Keyboard_Init(void);

// **************Keyboard_In*********************
// Input from keyboard's key inputs
// This function output just one event per key pressed
//  being necessary to release a key in order to press it again
// Input: none 
// Output: 0 to 15 depending on keys combination
unsigned long Keyboard_In(void);

// **************Keyboard_Continuous_In*********************
// Input from keyboard's key inputs
// This function output key pressed events in a progressive
//  way, where you can hold the button and the key event will
//  start to happen each time faster.
// Input: none 
// Output: 0 to 15 depending on keys combination
unsigned long Keyboard_Continuous_In(void);

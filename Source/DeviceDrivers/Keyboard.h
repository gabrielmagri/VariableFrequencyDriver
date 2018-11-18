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
#define DEBOUNCE_VALUE 8000

// The keys currently available to be read by this device driver
#define KEY_ONE   0X01
#define KEY_TWO   0X02
#define KEY_THREE 0X04
#define KEY_FOUR  0X08
#define KEY_FIVE  0X16
#define ENABLED_KEYS_MASK 0x1F

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

// **************Keyboard_InNoDebounce*********************
// Input from keyboard's key inputs
// This function output without debounce
// Input: none
// Output: 0 to 1F depending on keys combination
unsigned long Keyboard_InNoDebounce(void);

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

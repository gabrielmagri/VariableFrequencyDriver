/*
 * DisplayManager.h
 *
 *  Created on: Nov 8, 2018
 *      Author: GMAGRI
 */

#ifndef SOURCE_MAIN_DISPLAYMANAGER_H_
#define SOURCE_MAIN_DISPLAYMANAGER_H_

#include <stdbool.h>

/* A Unisinos 84x48 single color bitmap image to be displayed on startup */
static const unsigned char _logoUni[] ={
 0x42, 0x4D, 0xB6, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0x00, 0xF0, 0x0F, 0xFF, 0xFF, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F,
 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0x00,
 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0x00, 0x00,
 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x0F, 0xF0, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0x00, 0xF0, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xFF, 0xFF, 0xF0, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFF,
 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x0F, 0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0x00, 0xFF, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00,
 0x00, 0x0F, 0x00, 0x00, 0xFF, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0xF0, 0x0F,
 0x0F, 0x0F, 0xFF, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x0F,
 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x0F, 0x00, 0x0F, 0xFF, 0x00, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0xF0, 0x00, 0xFF, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0xFF, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x00,
 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F,
 0x00, 0xF0, 0xF0, 0x0F, 0x0F, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xFF, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x0F, 0xFF, 0x00, 0xFF, 0xFF, 0x0F, 0x00, 0x0F, 0x0F, 0xFF, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F,
 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0xFF, 0xF0, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0xFF, 0xF0,
 0x00, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0xFF, 0x00, 0x0F, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x0F, 0xF0,
 0xFF, 0xFF, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0x00,
 0xFF, 0x00, 0x0F, 0xF0, 0x0F, 0x00, 0x0F, 0xFF, 0x00, 0xFF, 0x0F, 0x00, 0x0F, 0xFF, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0xFF, 0x0F, 0xF0, 0x00, 0x0F, 0xF0, 0xF0, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0x00, 0x0F, 0xF0, 0x0F, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0xF0, 0x0F, 0x00, 0xFF, 0xFF,
 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0x00, 0x0F, 0xF0, 0x0F, 0x0F, 0xFF, 0x0F,
 0x00, 0xFF, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0x0F, 0x0F, 0xFF, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F,
 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0x00, 0x0F, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0x00, 0xFF, 0x0F, 0xFF, 0x00, 0x0F, 0x00, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0x0F, 0xF0, 0x00, 0x0F, 0xF0, 0xFF, 0xF0, 0x00,
 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0x00, 0x0F, 0xF0, 0x0F, 0xFF, 0x00, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 0xF0, 0xFF, 0x00, 0xF0,
 0x0F, 0xFF, 0x00, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x0F, 0xFF, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x0F, 0xFF, 0x00, 0x0F, 0xF0,
 0xFF, 0xF0, 0x00, 0x0F, 0x0F, 0xFF, 0x00, 0x0F, 0xFF, 0xF0, 0x0F, 0xF0, 0xFF, 0xF0, 0x00, 0x0F, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
};

/* ***************DisplayManager_Init******************
 * This function initialize all the device drivers
 * used and needed by this module
 * Input: none
 * Output: none
 */
void DisplayManager_Init(void);

/* ********DisplayManager_DisplayUnisinosLogo*********
 * This function clears the whole screen and update it
 * with a full 84x48 bmp UNISINOS logo image
 * Input: none
 * Output: none
 */
void DisplayManager_DisplayUnisinosLogo(void);


/* ******************displayOperationalInfo*************************
 * This function update the whole display screen with the operational
 * information, like motor status.
 * Input: none
 * Output: none
 */
void DisplayManager_OperationalInfo(MotorState state, unsigned short sFreq, unsigned short aFreq, bool smooth);

/* ******************DisplayManager_UpdatedMotorState*************************
 * This function provides a way to update a specific display position,
 * more precisely, the motor state position. It's update with the new state
 * Input: none
 * Output: none */
void DisplayManager_UpdatedMotorState(MotorState state);

/* ******************DisplayManager_ConfigInfo*************************
 * This function update the whole display screen with the configuration
 * information, configured timers, current selected time unit, current
 * selected timer to be updated.
 * Input: none
 * Output: none
 */
void DisplayManager_ConfigInfo(void);

/* **************DisplayManager_UpdatedTimes*********************
 * This function updates on the screen just the current
 * timers. Can be called after their changes
 * Input: none
 * Output: none
 */
void DisplayManager_UpdateSelectedFrequency(unsigned short freq);

/* **************DisplayManager_UpdateActualFrequency*********************
 * This function updates on the screen just the current
 * timers. Can be called after their changes
 * Input: none
 * Output: none
 */
void DisplayManager_UpdateActualFrequency(unsigned short freq);

/* **************DisplayManager_UpdateSmoothIndicator*********************
 * This function updates on the screen the smooth update indicator
 * Input: none
 * Output: none
 */
void DisplayManager_UpdateSmoothIndicator(bool smooth);

#endif /* SOURCE_MAIN_DISPLAYMANAGER_H_ */

/*
 * 7Segment.h
 *
 *  Created on: Sep 1, 2017
 *      Author: rik
 */

#include "stdint.h"

#define DOT		0x08
#define ONE  	0x50
#define TWO		0x67
#define THREE	0x75
#define FOUR	0xF0
#define FIVE	0xB5
#define SIX		0xB7
#define SEVEN	0x51
#define EIGHT	0xF7
#define NINE	0xF5
#define ZERO	0xD7

void SetDigitValue(uint8_t segment, uint8_t value, uint8_t dot);
void SetDigit(uint8_t value, uint8_t dot);
void SetSegment(uint8_t value);
void SetDisplay(uint8_t display[], uint8_t lenght);
void HandleDisplay();

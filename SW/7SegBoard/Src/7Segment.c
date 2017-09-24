/*
 * 7Segment.c
 *
 *  Created on: Sep 1, 2017
 *      Author: rik
 */

#include "7Segment.h"
#include "stm32f0xx_hal.h"

#define CLEAR		4

extern SPI_HandleTypeDef hspi1;

static uint8_t digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
uint8_t digits[4] = {0, 0, 0, 0};
uint8_t dots[4] = {0, 0, 0, 0};

void SetDigitValue(uint8_t segment, uint8_t value, uint8_t dot)
{
	if(segment <= 3)
	{
		digits[segment] = value;
		dots[segment] = dot;
	}
}

void SetDigit(uint8_t value, uint8_t dot)
{
	HAL_GPIO_WritePin(STREG_GPIO_Port, STREG_Pin, GPIO_PIN_RESET);
	uint8_t data[1];
	data[0] = digit[value];
	if(dot == 1)
	{
		data[0] += DOT;
	}
	HAL_SPI_Transmit(&hspi1, data, 1, 100);
	HAL_GPIO_WritePin(STREG_GPIO_Port, STREG_Pin, GPIO_PIN_SET);
}

void SetDisplay(uint8_t display[], uint8_t lenght)
{
	uint8_t segmentCounter = 0;
	for(int i = 0; i < lenght-1; i++)
	{
		if(display[i] >= 48 && display[i] <= 57)
		{	//It's 0-9
			if(display[i+1] == 46)
			{
				SetDigitValue(3-segmentCounter, display[i]-48, 1);
				i++;
			}
			else
			{
				SetDigitValue(3-segmentCounter, display[i]-48, 0);
			}
			segmentCounter++;
		}
	}
}

void SetSegment(uint8_t value)
{
	switch (value) {
	case 0:
		HAL_GPIO_WritePin(Segment4_GPIO_Port, Segment4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment3_GPIO_Port, Segment3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment2_GPIO_Port, Segment2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment1_GPIO_Port, Segment1_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(Segment1_GPIO_Port, Segment1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment3_GPIO_Port, Segment3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment4_GPIO_Port, Segment4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment2_GPIO_Port, Segment2_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(Segment2_GPIO_Port, Segment2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment4_GPIO_Port, Segment4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment1_GPIO_Port, Segment1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment3_GPIO_Port, Segment3_Pin, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(Segment3_GPIO_Port, Segment3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment2_GPIO_Port, Segment2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment1_GPIO_Port, Segment1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment4_GPIO_Port, Segment4_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(Segment3_GPIO_Port, Segment3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment2_GPIO_Port, Segment2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment1_GPIO_Port, Segment1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Segment4_GPIO_Port, Segment4_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void HandleDisplay()
{
	static uint8_t segment = 0;
	SetSegment(CLEAR);
	SetDigit(digits[segment], dots[segment]);
	SetSegment(segment);
	segment++;
	if(segment >= 4)
	{
		segment = 0;
	}
}

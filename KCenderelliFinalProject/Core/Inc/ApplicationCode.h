/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"
#include "GameDriver.h"

#include <stdio.h>


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

static volatile uint8_t touchPending = 0;
extern GameState * game;
extern RNG_HandleTypeDef hrng;

#define SHORT_MIN_MS   1000u


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void ApplicationInit(void);
void LCD_Visual_Demo(void);
void processTouchIfPending(void);

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */

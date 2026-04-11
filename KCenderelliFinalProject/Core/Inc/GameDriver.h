/*
 * GameDriver.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_GAMEDRIVER_H_
#define INC_GAMEDRIVER_H_

#include "OnePlayer.h"
#include "TwoPlayer.h"

extern GameState * game;

void setNewTouchFlag(uint16_t x, uint16_t y);
void TouchLogic(uint16_t x, uint16_t y);

uint8_t checkFlag(void);
void  resetFlag(void);
uint16_t getX(void);
uint16_t getY(void);

#endif /* INC_GAMEDRIVER_H_ */

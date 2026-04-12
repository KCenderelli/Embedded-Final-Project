/*
 * SharedPlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_SHAREDPLAYER_H_
#define INC_SHAREDPLAYER_H_

#include "GameDisplay.h"

#include <stdio.h>


#define Button_Press_MS   3000u

extern GameState * game;

void returnToStart(void);
void StartScreenTouchLogic(uint16_t x, uint16_t y);
void placeShips(uint16_t x, uint16_t y);
GameState * initGame(void);
uint8_t checkValidPlacement(int x, int y);
void buttonCheck(uint16_t x, uint16_t y);
uint8_t checkGuessValidPlacement(int x, int y);
void guessButtonCheck(uint16_t x, uint16_t y);
void nextButtonCheck(uint16_t x, uint16_t y);


#endif /* INC_SHAREDPLAYER_H_ */

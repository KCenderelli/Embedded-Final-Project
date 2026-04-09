/*
 * TwoPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "TwoPlayer.h"

void twoPlayerStartUp(void){
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
}

GameState twoPlayerGameLogic(GameState game, uint16_t x, uint16_t y){
	gridDisplay();
	return game;
}

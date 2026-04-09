/*
 * TwoPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "TwoPlayer.h"

GameState twoPlayerStartUp(GameState game, uint16_t x, uint16_t y){
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
	return game;
}

GameState twoPlayerGameLogic(GameState game, uint16_t x, uint16_t y){
	gridDisplay();
	return game;
}

/*
 * TwoPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "TwoPlayer.h"

extern GameState * game;

void twoPlayerStartUp(void){
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
	renderPlacementScreen();
	return;
}

void twoPlayerGameLogic(uint16_t x, uint16_t y){
	gridDisplay();
	return;
}

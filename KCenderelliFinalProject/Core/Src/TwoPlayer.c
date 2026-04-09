/*
 * TwoPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "TwoPlayer.h"

void twoPlayerStartUp(GameState * game){
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
	renderPlacementScreen(game);
	return;
}

void twoPlayerGameLogic(GameState  *game, uint16_t x, uint16_t y){
	gridDisplay();
	return;
}

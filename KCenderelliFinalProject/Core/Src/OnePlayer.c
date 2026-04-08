/*
 * OnePlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "OnePlayer.h"


GameState onePlayerStartUp(GameState game, uint16_t x, uint16_t y){
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
	game = placeShips(game, x, y);
	return game;
}

GameState onePlayerGameLogic(GameState game, uint16_t x, uint16_t y){
	gridDisplay();
	return game;
}

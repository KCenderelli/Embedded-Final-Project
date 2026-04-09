/*
 * OnePlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "OnePlayer.h"


void onePlayerStartUp(void){
    clearScreen();
    gridDisplay();
    rotationButtonDisplay();
}

void onePlayerPlaceShips(GameState * game, uint16_t x, uint16_t y){
    clearScreen();
    gridDisplay();
    rotationButtonDisplay();
    placeShips(game, x, y);
}

void onePlayerGameLogic(GameState * game, uint16_t x, uint16_t y){
	gridDisplay();
}

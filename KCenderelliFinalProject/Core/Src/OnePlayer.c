/*
 * OnePlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "OnePlayer.h"


void onePlayerStartUp(GameState * game){
    clearScreen();
    gridDisplay();
    rotationButtonDisplay();
    renderPlacementScreen(game);
    return;
}

void onePlayerPlaceShips(GameState * game, uint16_t x, uint16_t y){
    clearScreen();
    gridDisplay();
    rotationButtonDisplay();
    renderPlacementScreen(game);
    placeShips(game, x, y);
    return;
}

void onePlayerGameLogic(GameState * game, uint16_t x, uint16_t y){
	gridDisplay();
	return;
}

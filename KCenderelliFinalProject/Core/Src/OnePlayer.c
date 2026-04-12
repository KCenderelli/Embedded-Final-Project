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
    renderPlacementScreen();
    return;
}

void onePlayerPlaceShips(uint16_t x, uint16_t y){
    clearScreen();
    gridDisplay();
    rotationButtonDisplay();
	placeShips(x, y);
    buttonCheck(x, y);
    renderPlacementScreen();
    renderPlacedShips();
    return;
}

void AIPlaceShips(void)
{
	return;
}

void onePlayerGameLogic(uint16_t x, uint16_t y){
	gridDisplay();
	return;
}

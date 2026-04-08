/*
 * SharedPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#include "SharedPlayer.h"

uint16_t game_mode = START_SCREEN;

uint16_t StartScreenTouchLogic(uint16_t x, uint16_t y){
	if(x == 1 && y == 1)
	{
		game_mode = ONE_PLAYER;
		return game_mode;
	}
	else if (x == 2 && y == 2)
	{
		game_mode = TWO_PLAYER;
		return game_mode;
	}
	return game_mode;
}

void returnToStart(void){
	game_mode = START_SCREEN;
	startScreenDisplay();
}

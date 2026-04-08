/*
 * SharedPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#include "SharedPlayer.h"

volatile GameState game;

GameState StartScreenTouchLogic(uint16_t x, uint16_t y){
	if(y >= 140 && y <= 200)
	{
		game.mode = ONE_PLAYER_SETUP;
		return game;
	}
	else if (y >= 10 && y <140)
	{
		game.mode = TWO_PLAYER_SETUP;
		return game;
	}
	return game;
}

void returnToStart(void){
	game.mode = START_SCREEN;
	startScreenDisplay();
}

GameState placeShips(GameState game, uint16_t x, uint16_t y)
{
	ship2HorizontalDisplay(25, 25);
	if(x >= 10 && x <= 50 && y>= 255 && y<=300)
	{
		ship2HorizontalDisplay(25,25);
	}
	if(x > 50 && x <= 90 && y>= 255 && y<=300)
	{
		ship2HorizontalDisplay(55,25);
	}
	if(x > 90 && x <= 300 && y>= 255 && y<=300)
	{
		ship2HorizontalDisplay(75,25);
	}


//	game.Player1Ship2.boardlocation[x][y];
	return game;
}

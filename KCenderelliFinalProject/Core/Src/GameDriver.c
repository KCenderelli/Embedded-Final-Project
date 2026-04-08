/*
 * GameDriver.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "GameDriver.h"

extern volatile GameState game;

void TouchLogic(uint16_t x, uint16_t y){
	if(game.mode == START_SCREEN)
	{
		game = StartScreenTouchLogic(x,y);
		if(game.mode == ONE_PLAYER_SETUP)
		{
			game = onePlayerStartUp(game, x, y);
		}
		else if(game.mode == TWO_PLAYER_SETUP)
		{
			game = twoPlayerStartUp(game, x, y);
		}
	}
	else if (game.mode == ONE_PLAYER_SETUP)
	{

	}
	else if (game.mode == TWO_PLAYER_SETUP)
	{

	}
	else if(game.mode == ONE_PLAYER)
	{
		game = onePlayerGameLogic(game, x, y);
	}
	else if(game.mode == TWO_PLAYER)
	{
		game = twoPlayerGameLogic(game, x, y);
	}
}




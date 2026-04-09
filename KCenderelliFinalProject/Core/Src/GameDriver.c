/*
 * GameDriver.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "GameDriver.h"

extern GameState game;
uint16_t x_stored;
uint16_t y_stored;
static uint8_t statusFlag = 0;

void setNewTouchFlag(uint16_t x, uint16_t y){
	statusFlag = 1;
	x_stored = x;
	y_stored = y;
}

uint8_t checkFlag(void){
	return statusFlag;
}

void  resetFlag(void){
	statusFlag = 0;
	return;
}

uint16_t getX(void){
	return x_stored;
}

uint16_t getY(void){
	return y_stored;
}

void TouchLogic(GameState *game, uint16_t x, uint16_t y){
	if(game->mode == START_SCREEN)
	{
		StartScreenTouchLogic(game, x,y);
		if(game->mode == ONE_PLAYER_SETUP)
		{
			onePlayerStartUp(game);
			return;
		}
		else if(game->mode == TWO_PLAYER_SETUP)
		{
			twoPlayerStartUp(game);
			return;
		}
	}
	else if (game->mode == ONE_PLAYER_SETUP)
	{
		onePlayerPlaceShips(game, x, y);
		return;
	}
	else if (game->mode == TWO_PLAYER_SETUP)
	{
		onePlayerPlaceShips(game, x, y);
		return;
	}
	else if(game->mode == ONE_PLAYER)
	{
		onePlayerGameLogic(game, x, y);
		return;
	}
	else if(game->mode == TWO_PLAYER)
	{
		twoPlayerGameLogic(game, x, y);
		return;
	}
}




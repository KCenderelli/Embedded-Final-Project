/*
 * GameDriver.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "GameDriver.h"

extern GameState * game;
uint16_t x_stored;
uint16_t y_stored;
static uint8_t statusFlag = 0;

void setNewTouchFlag(uint16_t x, uint16_t y){
	if(statusFlag == 0)
	{
		statusFlag = 1;
		x_stored = x;
		y_stored = y;
	}
	return;
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

void TouchLogic(uint16_t x, uint16_t y){
	if(game->mode == START_SCREEN)
	{
		StartScreenTouchLogic(x,y);
		if(game->mode == ONE_PLAYER_SETUP)
		{
			onePlayerStartUp();
			return;
		}
		else if(game->mode == TWO_PLAYER_SETUP)
		{
			twoPlayerStartUp();
			return;
		}
	}
	else if (game->mode == ONE_PLAYER_SETUP)
	{
		onePlayerPlaceShips(x, y);
		return;
	}
	else if (game->mode == TWO_PLAYER_SETUP)
	{
		onePlayerPlaceShips(x, y);
		return;
	}
	else if(game->mode == ONE_PLAYER)
	{
		onePlayerGameLogic(x, y);
		return;
	}
	else if(game->mode == TWO_PLAYER)
	{
		twoPlayerGameLogic(x, y);
		return;
	}
}




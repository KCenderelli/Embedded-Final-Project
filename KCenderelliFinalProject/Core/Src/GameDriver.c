/*
 * GameDriver.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "GameDriver.h"

extern uint16_t game_mode;

void TouchLogic(uint16_t x, uint16_t y){
	if(game_mode == START_SCREEN)
	{
		game_mode = StartScreenTouchLogic(x,y);
		if(game_mode == ONE_PLAYER)
		{
			onePlayerStartUp();
		}
		if(game_mode == TWO_PLAYER)
		{
			twoPlayerStartUp();
		}
	}
	if(game_mode == ONE_PLAYER)
	{
		onePlayerGameLogic();
	}
	if(game_mode == TWO_PLAYER)
	{
		twoPlayerGameLogic();
	}
}




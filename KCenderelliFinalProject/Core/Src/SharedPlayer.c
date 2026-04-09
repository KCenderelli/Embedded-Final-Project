/*
 * SharedPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#include "SharedPlayer.h"

GameState game;

GameState initGame(void)
{
    GameState game = {0};

    game.mode = START_SCREEN;
    game.currentPlayer = 1;

    int lengths[3] = {2, 3, 4};
    for(int i = 0; i < 3; i++)
    {
        game.player1Ships[i].length = lengths[i];
        game.player2Ships[i].length = lengths[i];
    }

    game.placement.currentShipIndex = 0;
    game.placement.currentOrientation = HORIZONTAL;
    game.placement.previewX = 0;
    game.placement.previewY = 0;

    return game;
}


void StartScreenTouchLogic(GameState *game, uint16_t x, uint16_t y){
	if(y >= 140 && y <= 200)
	{
		game->mode = ONE_PLAYER_SETUP;
	}
	else if (y >= 10 && y <140)
	{
		game->mode = TWO_PLAYER_SETUP;
	}
	return;
}

void returnToStart(void){
	game.mode = START_SCREEN;
	startScreenDisplay();
	return;
}

void placeShips(GameState * game, uint16_t x, uint16_t y)
{
	int gridX = (x - 10) / 30;
	int gridY = (y - 10) / 30;

	game->placement.previewX = gridX;
	game->placement.previewY = gridY;

	return;
}

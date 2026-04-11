/*
 * SharedPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#include "SharedPlayer.h"

GameState gameInstance;
GameState * game = &gameInstance;


GameState * initGame(void)
{
    game->mode = START_SCREEN;
    game->currentPlayer = 1;

    int lengths[3] = {2, 3, 4};
    for(int i = 0; i < 3; i++)
    {
        game->player1Ships[i].length = lengths[i];
        game->player2Ships[i].length = lengths[i];
    }

    game->placement.currentShipIndex = 0;
    game->placement.currentOrientation = HORIZONTAL;
    game->placement.previewX = 0;
    game->placement.previewY = 0;

    return game;
}

void StartScreenTouchLogic(uint16_t x, uint16_t y){
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
	game->mode = START_SCREEN;
	startScreenDisplay();
	return;
}


uint8_t checkValidPlacement(int x, int y){
    if(x < 0 || y < 0) return 0;

    Ship * ship = &game->player1Ships[game->placement.currentShipIndex];

    if(game->placement.currentOrientation == HORIZONTAL)
    {
        if(x + ship->length > 7) return 0;  // ship runs off right edge
        if(y > 6)                return 0;
    }
    else // VERTICAL
    {
        if(x > 6)                return 0;
        if(y + ship->length > 7) return 0;  // ship runs off bottom edge
    }

    return 1;
}


void placeShips(uint16_t x, uint16_t y)
{
    int gridX = -1;
    int gridY = -1;
    if(y > 60)
    {
        if(y >= 140 && y <= 220)
        {
            gridY = game->placement.previewY;
            if(x < 84)
            {
                gridX = game->placement.previewX - 1;
                if(checkValidPlacement(gridX, gridY) == 1)
                {
                	printf("Before: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
                	game->placement.previewX = gridX;
                	printf("After: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
//                    game->placement.previewX = gridX;  // move left
                }
            }
            else if(x > 168)
            {
                gridX = game->placement.previewX + 1;
                if(checkValidPlacement(gridX, gridY) == 1)
                {
                	printf("Before: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
                	game->placement.previewX = gridX;
                	printf("After: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
//                    game->placement.previewX = gridX;  // move right
                }
            }
        }
        if(x >= 84 && x <= 168)
        {
        	gridX = game->placement.previewX;
            if(y < 190)
            {
                gridY = game->placement.previewY + 1;
				if(checkValidPlacement(gridX, gridY) == 1)
				{
					printf("Before: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
					game->placement.previewY = gridY;
					printf("After: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
//					game->placement.previewY = gridY;  // move down
				}
            }
            else if(y >= 190)
            {
                gridY = game->placement.previewY - 1;
				if(checkValidPlacement(gridX, gridY) == 1)
				{
					printf("Before: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
					game->placement.previewY = gridY;
					printf("After: previewX=%d previewY=%d\n", game->placement.previewX, game->placement.previewY);
//					game->placement.previewY = gridY;  // move up
				}
            }
		}
    }
}


void buttonCheck(uint16_t x, uint16_t y){
	if(y >= 0 && y <= 60)
	{
		if(x >= 30 && x<= 100)
		{
			if(game->placement.currentOrientation == VERTICAL)
			{
				game->placement.currentOrientation = HORIZONTAL;
				if(checkValidPlacement(game->placement.previewX, game->placement.previewY) == 0)
				{
					game->placement.currentOrientation = VERTICAL;
				}
			}
			else
			{
				game->placement.currentOrientation = VERTICAL;
				if(checkValidPlacement(game->placement.previewX, game->placement.previewY) == 0)
				{
					game->placement.currentOrientation = HORIZONTAL;
				}
			}
		}
//		else if(x > 100 && x<= 200)
//		{
//			//ADD SHIP TO PLAYERBOARD place
//		}
	}
}



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
    renderPlacedShips(1);
    if(game->placement.currentShipIndex == 3)
    {
    	game->mode = AI_SETUP;
    }
    return;
}

extern RNG_HandleTypeDef hrng;

void AIPlaceShips(void)
{
	game->currentPlayer = 0;
	game->placement.currentShipIndex = 0;

	for(int shipIndex = 0; shipIndex < 3; shipIndex++)
	{
		game->placement.currentShipIndex = shipIndex;
		uint8_t placed = 0;

		while(!placed)
		{
			uint32_t rng1, rng2, rng3;
			HAL_RNG_GenerateRandomNumber(&hrng, &rng1);
			HAL_RNG_GenerateRandomNumber(&hrng, &rng2);
			HAL_RNG_GenerateRandomNumber(&hrng, &rng3);

			int randX = rng1 % 7;
			int randY = rng2 % 7;
			game->placement.currentOrientation = (rng3 % 2 == 0) ? HORIZONTAL : VERTICAL;
			game->placement.previewX = randX;
			game->placement.previewY = randY;

			if(checkValidPlacement(randX, randY) == 1)
			{
				int shipLength = game->player2Ships[shipIndex].length;
				for(int i = 0; i < shipLength; i++)
				{
					if(game->placement.currentOrientation == HORIZONTAL)
						game->Player2Board[randY][randX + i] = 1;
					else
						game->Player2Board[randY + i][randX] = 1;
				}
				placed = 1;
			}
		}
	}
	game->mode = ONE_PLAYER_AI_REVEAL;
	AIDoneDisplay();
	nextButtonDisplay();
}



void onePlayerGuess(uint16_t x, uint16_t y){
    if(y > 60)
    {
        if(y >= 140 && y <= 220)
        {
            if(x < 84)
            {
            	uint16_t gridX = game->guess.previewX - 1;
            	if(gridX >= 0 && gridX <= 6)
            	{
					game->guess.previewX = gridX;
            	}
            }
            else if(x > 168)
            {
            	uint16_t gridX = game->guess.previewX + 1;
            	if(gridX >= 0 && gridX <= 6)
            	{
                	game->guess.previewX = gridX;
            	}
            }
        }
        if(x >= 84 && x <= 168)
        {
            if(y < 190)
            {
            	uint16_t gridY = game->guess.previewY + 1;
                if(gridY >= 0 && gridY <= 6)
                {
                	game->guess.previewY = gridY;
                }
            }
            else if(y >= 190)
            {
            	uint16_t gridY = game->guess.previewY - 1;
                if(gridY >= 0 && gridY <= 6)
                {
                	game->guess.previewY = gridY;
                }
            }
        }
    }
}

void onePlayerGameLogic(uint16_t x, uint16_t y){
    if(game->currentPlayer == 0)
    {
        if(y >= 0 && y <= 60)
        {
            nextButtonCheck(x, y);
        }
        else
        {
            clearScreen();
            gridDisplay();
            nextButtonDisplay();
            renderPlacedShips(1);
            renderGuesses();
        }
    }
    else if(game->currentPlayer == 1)
    {
        if(y >= 0 && y <= 60)
        {
            guessButtonCheck(x, y);
        }
        else
        {
            onePlayerGuess(x, y);
            clearScreen();
            gridDisplay();
            guessButtonDisplay();
            renderGuesses();
            drawGuessPreview();
        }
    }

    if(checkForWin() == 1){ player1WinDisplay(); return; }
    if(checkForWin() == 2){ AIWinDisplay(); return; }
}

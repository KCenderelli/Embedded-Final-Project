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
	game->currentPlayer = 1;
	game->placement.currentShipIndex = 0;
	game->placement.previewX = 0;
	game->placement.previewY = 0;
	game->mode = ONE_PLAYER;
}

void AIGuess(void)
{
    game->currentPlayer = 0;
    int gridX = -1;
    int gridY = -1;
    uint8_t guessSet = 0;

    for(int y = 0; y < 7 && !guessSet; y++)
    {
        for(int x = 0; x < 7 && !guessSet; x++)
        {
            if(game->Player2Guesses[y][x] == 2)
            {
                int neighborsX[4] = {x,   x,   x-1, x+1};
                int neighborsY[4] = {y-1, y+1, y,   y  };

                for(int n = 0; n < 4; n++)
                {
                    int nx = neighborsX[n];
                    int ny = neighborsY[n];
                    if(checkGuessValidPlacement(nx, ny) == 1)
                    {
                        gridX = nx;
                        gridY = ny;
                        guessSet = 1;
                        break;
                    }
                }
            }
        }
    }

    if(!guessSet)
    {
        while(!guessSet)
        {
            uint32_t rng1, rng2;
            HAL_RNG_GenerateRandomNumber(&hrng, &rng1);
            HAL_RNG_GenerateRandomNumber(&hrng, &rng2);

            gridX = rng1 % 7;
            gridY = rng2 % 7;

            if(checkGuessValidPlacement(gridX, gridY) == 1)
            {
                guessSet = 1;
            }
        }
    }

    if(game->Player1Board[gridY][gridX] == 1)
    {
        game->Player1Board[gridY][gridX] = 2;
        game->Player2Guesses[gridY][gridX] = 2;
    }
    else
    {
        game->Player2Guesses[gridY][gridX] = 1;
    }

    game->currentPlayer = 1;
}

void onePlayerGuess(uint16_t x, uint16_t y){
	int gridX = -1;
	int gridY = -1;
	if(y > 60)
	{
		if(y >= 140 && y <= 220)
		{
			gridY = game->guess.previewY;
			if(x < 84)
			{
				gridX = game->guess.previewX - 1;
				game->guess.previewX = gridX;
			}
			else if(x > 168)
			{
				gridX = game->guess.previewX + 1;
				game->guess.previewX = gridX;
			}
		}
		if(x >= 84 && x <= 168)
		{
			gridX = game->guess.previewX;
			if(y < 190)
			{
				gridY = game->guess.previewY + 1;
				game->guess.previewY = gridY;
			}
			else if(y >= 190)
			{
				gridY = game->guess.previewY - 1;
				game->guess.previewY = gridY;
			}
		}
	}
	return;
}


void onePlayerGameLogic(uint16_t x, uint16_t y){
    clearScreen();
    gridDisplay();

    if(game->mode == ONE_PLAYER_AI_REVEAL)
    {
        nextButtonDisplay();
        renderPlacedShips();
        renderGuesses();
        nextButtonCheck(x, y);
        return;
    }

    guessButtonDisplay();
    onePlayerGuess(x, y);
    guessButtonCheck(x, y);

    if(game->currentPlayer == 0)
    {

        AIGuess();
        game->mode = ONE_PLAYER_AI_REVEAL;
    }

    renderGuesses();
    drawGuessPreview();
    if(checkForWin() == 1)
    {
    	player1WinDisplay();
    }
    if(checkForWin() == 2)
	{
    	AIWinDisplay();
	}
    return;
}

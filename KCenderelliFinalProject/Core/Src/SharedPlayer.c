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
	for(int y = 0; y < 7; y++)
	{
	    for(int x = 0; x < 7; x++)
	    {
	        game->Player1Board[y][x] = 0;
	        game->Player2Board[y][x] = 0;
	    }
	}

	for(int y = 0; y < 7; y++)
		{
		    for(int x = 0; x < 7; x++)
		    {
		        game->Player1Guesses[y][x] = 0;
		        game->Player2Guesses[y][x] = 0;
		    }
		}

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

    game->guess.previewX = 0;
    game->guess.previewY = 0;

    return game;
}

void StartScreenTouchLogic(uint16_t x, uint16_t y){
	if(y >= 140 && y <= 200)
	{
		game->mode = ONE_PLAYER_SETUP;
		clearScreen();
		gridDisplay();
		rotationButtonDisplay();
		renderPlacementScreen();
	}
	else if (y >= 10 && y <140)
	{
		game->mode = TWO_PLAYER_SETUP;
		clearScreen();
		gridDisplay();
		rotationButtonDisplay();
		renderPlacementScreen();
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

    Ship * ship;
    if(game->currentPlayer == 1)
        ship = &game->player1Ships[game->placement.currentShipIndex];
    else
        ship = &game->player2Ships[game->placement.currentShipIndex];

    if(game->placement.currentOrientation == HORIZONTAL)
    {
        if(x + ship->length > 7) return 0;
        if(y > 6)                return 0;
        for(int i = 0; i < ship->length; i++)
        {
            if(game->currentPlayer == 1 && game->Player1Board[y][x + i] != 0) return 0;
            if((game->currentPlayer == 0 || game->currentPlayer == 2) &&
                game->Player2Board[y][x + i] != 0) return 0;
        }
    }
    else
    {
        if(x > 6)                return 0;
        if(y + ship->length > 7) return 0;
        for(int i = 0; i < ship->length; i++)
        {
            if(game->currentPlayer == 1 && game->Player1Board[y + i][x] != 0) return 0;
            if((game->currentPlayer == 0 || game->currentPlayer == 2) &&
                game->Player2Board[y + i][x] != 0) return 0;
        }
    }

    return 1;
}




uint8_t checkValidDisplay(int x, int y){
    if(x < 0 || y < 0) return 0;

    Ship * ship;
    if(game->currentPlayer == 1)
        ship = &game->player1Ships[game->placement.currentShipIndex];
    else
        ship = &game->player2Ships[game->placement.currentShipIndex];

    if(game->placement.currentOrientation == HORIZONTAL)
    {
        if(x + ship->length > 7) return 0;
        if(y > 6)                return 0;
    }
    else
    {
        if(x > 6)                return 0;
        if(y + ship->length > 7) return 0;
    }

    return 1;
}

uint8_t checkGuessValidPlacement(int x, int y){
    if(x < 0 || y < 0) return 0;
    if(x > 6 || y > 6) return 0;
    if(game->currentPlayer == 1 && game->Player1Guesses[y][x] != 0) return 0;
    if((game->currentPlayer == 0 || game->currentPlayer == 2)
        && game->Player2Guesses[y][x] != 0) return 0;
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
                if(checkValidDisplay(gridX,gridY) == 1)
                {
                	game->placement.previewX = gridX;
                }
            }
            else if(x > 168)
            {
                gridX = game->placement.previewX + 1;
                if(checkValidDisplay(gridX,gridY) == 1)
                {
                	game->placement.previewX = gridX;
                }
            }
        }
        if(x >= 84 && x <= 168)
        {
        	gridX = game->placement.previewX;
            if(y < 190)
            {
                gridY = game->placement.previewY + 1;
                if(checkValidDisplay(gridX,gridY) == 1)
                {
                	game->placement.previewY = gridY;
                }
            }
            else if(y >= 190)
            {
                gridY = game->placement.previewY - 1;
                if(checkValidDisplay(gridX,gridY) == 1)
                {
                	game->placement.previewY = gridY;
                }
            }
		}
    }
}


void buttonCheck(uint16_t x, uint16_t y){
	if(y >= 0 && y <= 60)
	{
		int gridX = game->placement.previewX;
		int gridY = game->placement.previewY;
		if(x >= 30 && x<= 100)
		{
			if(game->placement.currentOrientation == VERTICAL)
			{
				game->placement.currentOrientation = HORIZONTAL;
				if(checkValidDisplay(gridX, gridY) == 1)
				{
					game->placement.currentOrientation = HORIZONTAL;
				}
				else
				{
					game->placement.currentOrientation = VERTICAL;
				}
			}
			else
			{
				game->placement.currentOrientation = VERTICAL;
				if(checkValidDisplay(gridX, gridY) == 1)
				{
					game->placement.currentOrientation = VERTICAL;
				}
				else
				{
					game->placement.currentOrientation = HORIZONTAL;
				}
			}
		}
		else if(x > 100 && x<= 200)
		{
			int gridX = game->placement.previewX;
			int gridY = game->placement.previewY;
			if(checkValidPlacement(gridX, gridY) == 1){
				if(game->currentPlayer == 0)
				{
				    for(int i = 0; i < game->player2Ships[game->placement.currentShipIndex].length; i++)
				    {
				        if(game->placement.currentOrientation == HORIZONTAL)
				            game->Player2Board[gridY][gridX + i] = 1;
				        else
				            game->Player2Board[gridY + i][gridX] = 1;
				    }
				    if(game->placement.currentShipIndex < 2)
				    {
				        game->placement.currentShipIndex++;
				        game->placement.previewX = 0;
				        game->placement.previewY = 0;
				    }
				}
				else if (game->currentPlayer == 1)
				{
					for(int i = 0; i < game->player1Ships[game->placement.currentShipIndex].length; i++)
					{
					    if(game->placement.currentOrientation == HORIZONTAL)
					        game->Player1Board[gridY][gridX + i] = 1;
					    else
					        game->Player1Board[gridY + i][gridX] = 1;
					}
					if(game->placement.currentShipIndex < 2)
					{
						game->placement.currentShipIndex++;
						game->placement.previewX = 0;
						game->placement.previewY = 0;
						game->placement.currentOrientation = HORIZONTAL;
					}
					else
					{
						if(game->mode == ONE_PLAYER_SETUP)
						{
							game->currentPlayer = 0;
							game->mode = AI_SETUP;
						}
						else if(game->mode == TWO_PLAYER_SETUP && game->currentPlayer == 1)
						{
							game->currentPlayer = 2;
							game->placement.currentShipIndex = 0;
							game->placement.currentOrientation = HORIZONTAL;
							game->placement.previewX = 0;
							game->placement.previewY = 0;

							clearScreen();
							gridDisplay();
							rotationButtonDisplay();
							renderPlacementScreen();
							renderPlacedShips(game->currentPlayer);
						}
					}
				}
				else if(game->currentPlayer == 2)
				{
				    for(int i = 0; i < game->player2Ships[game->placement.currentShipIndex].length; i++)
				    {
				        if(game->placement.currentOrientation == HORIZONTAL)
				            game->Player2Board[gridY][gridX + i] = 1;
				        else
				            game->Player2Board[gridY + i][gridX] = 1;
				    }
				    if(game->placement.currentShipIndex < 2)
				    {
				        game->placement.currentShipIndex++;
				        game->placement.previewX = 0;
				        game->placement.previewY = 0;
				    }
				    else
				    {
				    	game->currentPlayer = 1;
						game->mode = TWO_PLAYER_P1_TURN;

						clearScreen();
						Player1TurnDisplay();
						nextButtonDisplay();
				    }
				}
			}
		}
	}
}


void nextButtonCheck(uint16_t x, uint16_t y){
    if(y >= 0 && y <= 60)
    {
    	game->guess.previewX = 0;
    	game->guess.previewY = 0;
		if(game->mode == ONE_PLAYER_AI_REVEAL)
		{
			game->mode = ONE_PLAYER;
			game->currentPlayer = 1;
			clearScreen();
			gridDisplay();
			guessButtonDisplay();
			renderGuesses();
			drawGuessPreview();
        }
		else if(game->mode == TWO_PLAYER_P1_TURN)
		{
			game->mode = TWO_PLAYER;
			game->currentPlayer = 1;
			clearScreen();
			gridDisplay();
			guessButtonDisplay();
			renderGuesses();
			drawGuessPreview();
		}
		else if(game->mode == TWO_PLAYER_P2_TURN)
		{
			game->mode = TWO_PLAYER;
			game->currentPlayer = 2;
			clearScreen();
			gridDisplay();
			guessButtonDisplay();
			renderGuesses();
			drawGuessPreview();
		}
    }
}


extern RNG_HandleTypeDef hrng;

void AIGuess(void)
{
    game->currentPlayer = 0;
    uint8_t hitAgain = 1;

    while(hitAgain)
    {
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
                    guessSet = 1;
            }
        }

        if(game->Player1Board[gridY][gridX] == 1)
        {
            game->Player1Board[gridY][gridX] = 2;
            game->Player2Guesses[gridY][gridX] = 2;
            hitAgain = 1;
        }
        else
        {
            game->Player2Guesses[gridY][gridX] = 1;
            hitAgain = 0;
        }
    }


    game->mode = ONE_PLAYER_AI_REVEAL;
    clearScreen();
    gridDisplay();
    nextButtonDisplay();
    renderPlacedShips(1);
    renderGuesses();
}


void guessButtonCheck(uint16_t x, uint16_t y){
    if(y >= 0 && y <= 60)
    {
        int gridX = game->guess.previewX;
        int gridY = game->guess.previewY;

        if(checkGuessValidPlacement(gridX, gridY) == 1)
        {
            if(game->currentPlayer == 1)
            {
                if(game->Player2Board[gridY][gridX] == 1)
                {
                    game->Player2Board[gridY][gridX] = 2;
                    game->Player1Guesses[gridY][gridX] = 2;
                    game->guess.previewX = 0;
                    game->guess.previewY = 0;
                    clearScreen();
                    gridDisplay();
                    guessButtonDisplay();
                    renderGuesses();
                    drawGuessPreview();
                }
                else
                {
                    game->Player1Guesses[gridY][gridX] = 1;
                    game->guess.previewX = 0;
                    game->guess.previewY = 0;

                    if(game->mode == ONE_PLAYER)
                    {
                        game->currentPlayer = 0;
                        AIGuess();
                    }
                    else if(game->mode == TWO_PLAYER)
                    {
                        game->currentPlayer = 2;
                        game->mode = TWO_PLAYER_P2_TURN;
                        clearScreen();
                        Player2TurnDisplay();
                        nextButtonDisplay();
                    }
                }
            }
            else if(game->currentPlayer == 2)
            {
                if(game->Player1Board[gridY][gridX] == 1)
                {
                    game->Player1Board[gridY][gridX] = 2;
                    game->Player2Guesses[gridY][gridX] = 2;
                    game->guess.previewX = 0;
                    game->guess.previewY = 0;
                    clearScreen();
                    gridDisplay();
                    guessButtonDisplay();
                    renderGuesses();
                    drawGuessPreview();
                }
                else
                {
                    game->Player2Guesses[gridY][gridX] = 1;
                    game->guess.previewX = 0;
                    game->guess.previewY = 0;
                    game->currentPlayer = 1;
                    game->mode = TWO_PLAYER_P1_TURN;
                    clearScreen();
                    Player1TurnDisplay();
                    nextButtonDisplay();
                }
            }
        }
    }
}

uint8_t checkForWin(void){
    uint8_t p1_hits = 0;
    uint8_t p2_hits = 0;

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(game->Player1Board[i][j] == 2){
                p1_hits++;
            }
            if(game->Player2Board[i][j] == 2){
                p2_hits++;
            }
        }
    }

    if(p1_hits == 9){
        return 2;
    }
    if(p2_hits == 9){
        return 1;
    }

    return 0;
}

/*
 * TwoPlayer.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */
#include "TwoPlayer.h"

extern GameState * game;

void twoPlayerStartUp(void){
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
	renderPlacementScreen();
	return;
}

void twoPlayerPlaceShips(int x,int y)
{
	clearScreen();
	gridDisplay();
	rotationButtonDisplay();
	placeShips(x, y);
	buttonCheck(x, y);
	renderPlacementScreen();
	renderPlacedShips(game->currentPlayer);
	if(game->mode == TWO_PLAYER_P1_TURN)
	{
		clearScreen();
		Player1TurnDisplay();
		nextButtonDisplay();
	}
	return;
}



void twoPlayerGuess(uint16_t x, uint16_t y){
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

void twoPlayerGameLogic(uint16_t x, uint16_t y){
    if(y >= 0 && y <= 60 && game->mode == TWO_PLAYER)
    {
        guessButtonCheck(x, y);
    }
    else if(y >= 0 && y <= 60 && game->mode == TWO_PLAYER_P1_TURN)
    {
    	nextButtonCheck(x, y);
    }
    else if(y >= 0 && y <= 60 && game->mode == TWO_PLAYER_P2_TURN)
    {
    	nextButtonCheck(x, y);
    }
    else
    {
    	twoPlayerGuess(x, y);
        clearScreen();
        gridDisplay();
        guessButtonDisplay();
        renderGuesses();
        drawGuessPreview();
    }

    if(checkForWin() == 1){ player1WinDisplay(); return; }
    if(checkForWin() == 2){ player2WinDisplay(); return; }
}

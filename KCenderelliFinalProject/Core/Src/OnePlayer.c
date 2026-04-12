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
}

void onePlayerGuess(uint16_t x, uint16_t y){
    clearScreen();
    gridDisplay();
    renderPlacedShips();
    return;
}

void onePlayerGameLogic(uint16_t x, uint16_t y){
	clearScreen();
	gridDisplay();
	renderPlacedShips();
	onePlayerGuess(x, y);
	return;
}

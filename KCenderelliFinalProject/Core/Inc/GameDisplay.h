/*
 * GameDisplay.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_GAMEDISPLAY_H_
#define INC_GAMEDISPLAY_H_

#include "LCD_Driver.h"



typedef enum {
	START_SCREEN,
	ONE_PLAYER_SETUP,
	TWO_PLAYER_SETUP,
    ONE_PLAYER,
	TWO_PLAYER,
    MODE_GAME_OVER
} GameMode;

typedef enum {
    HORIZONTAL,
    VERTICAL
} Orientation;


typedef struct {
    int currentShipIndex;
    Orientation currentOrientation;
    int previewX;
    int previewY;
} PlacementState;

typedef struct {
    int length;
    int x;
    int y;
    Orientation orient;
    int hits[4];
} Ship;

typedef struct {
    GameMode mode;
    int Player1Board[7][7];
    int Player2Board[7][7];
    // 0 == empty
    // 1 == ship located
    // 2 == hit
    int currentPlayer;
    //0 = AI
    //1 = Player 1
    //2 = Player 2
    Ship player1Ships[3];
    Ship player2Ships[3];
    PlacementState placement;
} GameState;


void startScreenDisplay(void);
void gridDisplay(void);
void rotationButtonDisplay(void);
void player1BoardDisplay(void);
void player2BoardDisplay(void);
void renderPlacementScreen(GameState * game);
void renderPlacedShips(GameState *game);
void drawShipPreview(Ship ship);

#endif /* INC_GAMEDISPLAY_H_ */

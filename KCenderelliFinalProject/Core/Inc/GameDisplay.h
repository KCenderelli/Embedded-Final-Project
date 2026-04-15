/*
 * GameDisplay.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_GAMEDISPLAY_H_
#define INC_GAMEDISPLAY_H_

#include "LCD_Driver.h"

#include <stdio.h>

typedef enum {
	START_SCREEN,
	ONE_PLAYER_SETUP,
	AI_SETUP,
	TWO_PLAYER_SETUP,
    ONE_PLAYER,
	ONE_PLAYER_AI_REVEAL,
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
    int previewX;
    int previewY;
} GussState;


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

    int Player1Guesses[7][7];
    int Player2Guesses[7][7];
    // 0 == Empty/Not Guessed
    // 1 == Miss
    // 2 == Hit

    int currentPlayer;
    //0 = AI
    //1 = Player 1
    //2 = Player 2
    Ship player1Ships[3];
    Ship player2Ships[3];
    PlacementState placement;
    GussState guess;
} GameState;

extern GameState * game;


void startScreenDisplay(void);
void gridDisplay(void);
void rotationButtonDisplay(void);
void player1BoardDisplay(void);
void player2BoardDisplay(void);
void renderPlacementScreen(void);
void renderPlacedShips(int player);
void drawShipPreview(void);
void drawGuessPreview(void);
void renderGuesses(void);
void guessButtonDisplay(void);
void nextButtonDisplay(void);
void player1WinDisplay(void);
void player2WinDisplay(void);
void AIWinDisplay(void);
void AIDoneDisplay(void);


#endif /* INC_GAMEDISPLAY_H_ */

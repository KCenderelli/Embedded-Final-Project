/*
 * SharedPlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_SHAREDPLAYER_H_
#define INC_SHAREDPLAYER_H_

#include "GameDisplay.h"

typedef enum {
	START_SCREEN,
	ONE_PLAYER_SETUP,
	TWO_PLAYER_SETUP,
    ONE_PLAYER,
	TWO_PLAYER,
    MODE_GAME_OVER
} GameMode;

typedef struct {
	int partsHit[2];
	int boardlocation[7][7];
} Ship2;

typedef struct {
	int partsHit[3];
	int boardlocation[7][7];
} Ship3;

typedef struct {
	int partsHit[4];
	int boardlocation[7][7];
} Ship4;


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
    Ship2 Player1Ship2;
    Ship2 Player2Ship2;

    Ship3 Player1Ship3;
    Ship3 Player2Ship3;

    Ship4 Player1Ship4;
    Ship4 Player2Ship4;
} GameState;

#define Button_Press_MS   3000u

void returnToStart(void);
GameState StartScreenTouchLogic(uint16_t x, uint16_t y);
GameState placeShips(GameState game, uint16_t x, uint16_t y);



#endif /* INC_SHAREDPLAYER_H_ */

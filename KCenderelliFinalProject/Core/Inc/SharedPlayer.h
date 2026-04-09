/*
 * SharedPlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_SHAREDPLAYER_H_
#define INC_SHAREDPLAYER_H_

#include "GameDisplay.h"


#define Button_Press_MS   3000u

void returnToStart(void);
void StartScreenTouchLogic(GameState *game, uint16_t x, uint16_t y);
void placeShips(GameState * game, uint16_t x, uint16_t y);
GameState initGame(void);


#endif /* INC_SHAREDPLAYER_H_ */

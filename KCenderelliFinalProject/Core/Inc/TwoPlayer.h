/*
 * TwoPlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_TWOPLAYER_H_
#define INC_TWOPLAYER_H_

#include "SharedPlayer.h"

GameState twoPlayerStartUp(GameState game, uint16_t x, uint16_t y);
GameState twoPlayerGameLogic(GameState game, uint16_t x, uint16_t y);

#endif /* INC_TWOPLAYER_H_ */

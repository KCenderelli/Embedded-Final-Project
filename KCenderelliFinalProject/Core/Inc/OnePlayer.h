/*
 * OnePlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_ONEPLAYER_H_
#define INC_ONEPLAYER_H_

#include "SharedPlayer.h"

GameState onePlayerStartUp(GameState game, uint16_t x, uint16_t y);
GameState onePlayerGameLogic(GameState game, uint16_t x, uint16_t y);

#endif /* INC_ONEPLAYER_H_ */

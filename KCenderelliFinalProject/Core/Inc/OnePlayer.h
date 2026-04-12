/*
 * OnePlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_ONEPLAYER_H_
#define INC_ONEPLAYER_H_

#include "SharedPlayer.h"

extern GameState * game;

void onePlayerStartUp(void);
void onePlayerGameLogic(uint16_t x, uint16_t y);
void onePlayerPlaceShips(uint16_t x, uint16_t y);
void AIPlaceShips(void);

#endif /* INC_ONEPLAYER_H_ */

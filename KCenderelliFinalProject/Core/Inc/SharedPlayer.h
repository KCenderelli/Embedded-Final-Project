/*
 * SharedPlayer.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_SHAREDPLAYER_H_
#define INC_SHAREDPLAYER_H_

#include "GameDisplay.h"

#define START_SCREEN 0
#define ONE_PLAYER 1
#define TWO_PLAYER 2

#define Button_Press_MS   3000u

void returnToStart(void);
uint16_t StartScreenTouchLogic(uint16_t x, uint16_t y);


#endif /* INC_SHAREDPLAYER_H_ */

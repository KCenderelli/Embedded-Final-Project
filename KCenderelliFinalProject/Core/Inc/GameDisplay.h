/*
 * GameDisplay.h
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */

#ifndef INC_GAMEDISPLAY_H_
#define INC_GAMEDISPLAY_H_

#include "LCD_Driver.h"

void startScreenDisplay(void);
void gridDisplay(void);
void rotationButtonDisplay(void);
void player1BoardDisplay(void);
void player2BoardDisplay(void);

void ship2HorizontalDisplay(int x, int y);
void ship2VerticalDisplay(int x, int y);

#endif /* INC_GAMEDISPLAY_H_ */

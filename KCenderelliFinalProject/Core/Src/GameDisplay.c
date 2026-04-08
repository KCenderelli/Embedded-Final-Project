/*
 * GameDisplay.c
 *
 *  Created on: Mar 31, 2026
 *      Author: Kirac
 */


#include "GameDisplay.h"

void startScreenDisplay(void){
//	for(uint16_t x = 0; x < (LCD_PIXEL_WIDTH_X/5)-1; x++){
//			for(uint16_t y = 0; y < (LCD_PIXEL_HEIGHT_Y/5)-1; y++){
//				LCD_Draw_Circle_Fill((5*x)+3,(5*y)+3,3,(LCD_COLOR_LIGHTERBLUE+(x*y)));
//			}
//		}
	LCD_Clear(LCD_COLOR_LIGHTERBLUE);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(10,10,'B');
	LCD_DisplayChar(25,10,'A');
	LCD_DisplayChar(40,10,'T');
	LCD_DisplayChar(55,10,'T');
	LCD_DisplayChar(70,10,'L');
	LCD_DisplayChar(85,10,'E');

	LCD_DisplayChar(115,10,'S');
	LCD_DisplayChar(130,10,'H');
	LCD_DisplayChar(140,10,'I');
	LCD_DisplayChar(150,10,'P');


	LCD_Draw_Circle_Fill(55,250,40,LCD_COLOR_LIGHTBLUE);
	LCD_Draw_Circle_Fill(185,250,40,LCD_COLOR_LIGHTBLUE);

	LCD_Draw_Square_Fill(55,250,40, 40,LCD_COLOR_BLACK);

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font12x12);

	LCD_DisplayChar(55,250,'O');
//	LCD_DisplayChar(25,10,'N');
//	LCD_DisplayChar(40,10,'E');
//
//	LCD_DisplayChar(115,10,'P');
//	LCD_DisplayChar(130,10,'L');
//	LCD_DisplayChar(140,10,'A');
//	LCD_DisplayChar(150,10,'Y');
//	LCD_DisplayChar(140,10,'E');
//	LCD_DisplayChar(150,10,'R');

	LCD_DisplayChar(185,250,'T');
//	LCD_DisplayChar(25,10,'W');
//	LCD_DisplayChar(40,10,'O');
//
//	LCD_DisplayChar(115,10,'P');
//	LCD_DisplayChar(130,10,'L');
//	LCD_DisplayChar(140,10,'A');
//	LCD_DisplayChar(150,10,'Y');
//	LCD_DisplayChar(140,10,'E');
//	LCD_DisplayChar(150,10,'R');
}

void gridDisplay(void){
	LCD_Draw_Vertical_Line(10,10,250,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(230,10,250,LCD_COLOR_BLACK);
}


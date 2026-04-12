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


//	LCD_Draw_Circle_Fill(55,250,40,LCD_COLOR_LIGHTBLUE);
//	LCD_Draw_Circle_Fill(185,250,40,LCD_COLOR_LIGHTBLUE);

	LCD_Draw_Square_Fill(125,150,40,90,LCD_COLOR_LIGHTBLUE);
	LCD_Draw_Square_Fill(125,250,40,90,LCD_COLOR_LIGHTBLUE);


	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font12x12);

	LCD_DisplayChar(55,150,'O');
	LCD_DisplayChar(65,150,'N');
	LCD_DisplayChar(75,150,'E');

	LCD_DisplayChar(95,150,'P');
	LCD_DisplayChar(105,150,'L');
	LCD_DisplayChar(115,150,'A');
	LCD_DisplayChar(125,150,'Y');
	LCD_DisplayChar(135,150,'E');
	LCD_DisplayChar(145,150,'R');

	LCD_DisplayChar(55,250,'T');
	LCD_DisplayChar(65,250,'W');
	LCD_DisplayChar(75,250,'O');

	LCD_DisplayChar(95,250,'P');
	LCD_DisplayChar(105,250,'L');
	LCD_DisplayChar(115,250,'A');
	LCD_DisplayChar(125,250,'Y');
	LCD_DisplayChar(135,250,'E');
	LCD_DisplayChar(145,250,'R');
	return;
}

void gridDisplay(void){
	LCD_Draw_Vertical_Line(10,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(40,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(70,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(100,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(130,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(160,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(190,10,210,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(220,10,210,LCD_COLOR_BLACK);


	LCD_Draw_Horizontal_Line(10, 10, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 40, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 70, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 100, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 130, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 160, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 190, 210, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(10, 220, 210, LCD_COLOR_BLACK);
	return;
}


void rotationButtonDisplay(void){
	LCD_Draw_Square_Fill(70,270,40,40,LCD_COLOR_LIGHTBLUE);
	LCD_DisplayChar(35,270,'R');
	LCD_DisplayChar(45,270,'O');
	LCD_DisplayChar(55,270,'T');
	LCD_DisplayChar(65,270,'A');
	LCD_DisplayChar(75,270,'T');
	LCD_DisplayChar(85,270,'E');

	LCD_Draw_Square_Fill(180,270,40,40,LCD_COLOR_LIGHTBLUE);
	LCD_DisplayChar(145,270,'P');
	LCD_DisplayChar(155,270,'L');
	LCD_DisplayChar(165,270,'A');
	LCD_DisplayChar(175,270,'C');
	LCD_DisplayChar(185,270,'E');
	return;
}

void drawShipPreview(void)
{
	Ship previewShip;

	previewShip.length = game->player1Ships[game->placement.currentShipIndex].length;
	previewShip.x = game->placement.previewX;
	previewShip.y = game->placement.previewY;
	previewShip.orient = game->placement.currentOrientation;

    for(int i = 0; i < previewShip.length; i++)
    {
        int gridX = previewShip.x;
        int gridY = previewShip.y;

        if(previewShip.orient == HORIZONTAL)
            gridX += i;
        else
            gridY += i;

        int pixelX = 10 + gridX * 30 + 15;
        int pixelY = 10 + gridY * 30 + 15;

        LCD_Draw_Circle_Fill(pixelX, pixelY, 10, LCD_COLOR_LIGHTBLUE);
    }
    return;
}


void renderPlacementScreen(void)
{
    printf("Rendering at: x=%d y=%d\n", game->placement.previewX, game->placement.previewY);

    drawShipPreview();
    return;
}

void renderPlacedShips(void){
    for(int y = 0; y < 7; y++)
    {
        for(int x = 0; x < 7; x++)
        {
            if(game->Player1Board[y][x] == 1)
            {
                int pixelX = 10 + x * 30 + 15;  // x → pixelX
                int pixelY = 10 + y * 30 + 15;  // y → pixelY
                LCD_Draw_Circle_Fill(pixelX, pixelY, 10, LCD_COLOR_BLUE);
            }
            if(game->Player1Board[y][x] == 2)
            {
                int pixelX = 10 + x * 30 + 15;
                int pixelY = 10 + y * 30 + 15;
                LCD_Draw_Circle_Fill(pixelX, pixelY, 10, LCD_COLOR_BLACK);
            }
        }
    }
}

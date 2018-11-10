#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "chain.h"

extern int rows, columns, speed;

/* All the functions to show content on window are written here */

/* create a board of set rows and columns */
void AD_CreateBoard(SDL_Renderer **ren, int r, int g, int b, int a) {
	int i;
	SDL_SetRenderDrawColor(*ren, r, g, b, a);
	for(i = 0; i <= columns; i++)
		SDL_RenderDrawLine(*ren, i * CELL_SIDE, 0, i * CELL_SIDE, rows * CELL_SIDE);
	for(i = 0; i <= rows; i++)
		SDL_RenderDrawLine(*ren, 0, i * CELL_SIDE, columns * CELL_SIDE, i * CELL_SIDE);	
}	

/* check board information and draw accordingly the balls in each cells of respective player */
void UpdateBoardStatus(SDL_Renderer **ren, board b) {
	int i, j, Vstate;
	static short int vibration = 0, direction = 1;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < columns; j++) {
			if(b[i][j].balls == b[i][j].capacity && speed != -1)
				Vstate = vibration;
			else
				Vstate = 0;	
			switch(b[i][j].balls) {
				case 0:
					break;
				case 1:
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) + Vstate, CELL_SIDE * (i + 0.5) + Vstate, CELL_SIDE * (28.0 / 80.0), (b[i][j].p)->r, (b[i][j].p)->g, (b[i][j].p)->b, (b[i][j].p)->a);
					break;
				case 2:
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) - CELL_SIDE * (12.0 / 80.0) + Vstate, CELL_SIDE * (i + 0.5) - CELL_SIDE * (12.0 / 80.0), CELL_SIDE * (21.0 / 80.0) + Vstate + CELL_SIDE / 15, (b[i][j].p)->r, (b[i][j].p)->g, (b[i][j].p)->b, (b[i][j].p)->a);
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) + CELL_SIDE * (12.0 / 80.0) - Vstate, CELL_SIDE * (i + 0.5) + CELL_SIDE * (12.0 / 80.0), CELL_SIDE * (21.0 / 80.0) + Vstate + CELL_SIDE / 15, (b[i][j].p)->r, (b[i][j].p)->g, (b[i][j].p)->b, (b[i][j].p)->a);
					break;
				case 3:
				 	AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) - CELL_SIDE * (15.0 / 80.0) - Vstate, CELL_SIDE * (i + 0.5) - CELL_SIDE * (15.0 / 80.0), CELL_SIDE * (25.0 / 80.0), (b[i][j].p)->r, (b[i][j].p)->g, (b[i][j].p)->b, (b[i][j].p)->a);
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) + CELL_SIDE * (15.0 / 80.0) + Vstate, CELL_SIDE * (i + 0.5) - CELL_SIDE * (15.0 / 80.0), CELL_SIDE * (25.0 / 80.0), (b[i][j].p)->r, (b[i][j].p)->g, (b[i][j].p)->b, (b[i][j].p)->a);
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5), CELL_SIDE * (i + 0.5) + CELL_SIDE * (15.0 / 80.0) + Vstate, CELL_SIDE * (25.0 / 80.0), (b[i][j].p)->r, (b[i][j].p)->g, (b[i][j].p)->b, (b[i][j].p)->a);
					break;				 	
				default:
					break;	
			}
		}
	}
	vibration += direction;
	if(vibration >= (CELL_SIDE / 35) || vibration <= (-1 * (CELL_SIDE / 35)))
		direction *= -1;
	return;				
}

/* a function to draw circle of radius "radius" at given coordinates and with provided r, g, b, a values */
void AD_DrawCircle(SDL_Renderer **ren, float center_x_coordinate, float center_y_coordinate, float radius, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(*ren, r, g, b, a);
	int x;
	float y;
	for(x = 0; x <= radius; x++) {
		y = sqrt(radius * radius - (float)(x * x));
		SDL_RenderDrawLine(*ren, center_x_coordinate + x, center_y_coordinate + y, center_x_coordinate + x, center_y_coordinate - y);
		SDL_RenderDrawLine(*ren, center_x_coordinate - x, center_y_coordinate + y, center_x_coordinate - x, center_y_coordinate - y);
	}
}

#include <stdio.h>
#include <SDL2/SDL.h>
#include "chain.h"
#include <time.h>

extern int rows, columns;



void AD_AnimateScreen(SDL_Renderer **ren, board b, player *current) {
	int pos, i, j;
	for(pos = 0; pos <= CELL_SIDE; pos += 5) {
		SDL_SetRenderDrawColor(*ren, 0, 0, 0, 0);
		SDL_RenderClear(*ren);
		for(i = 0; i < rows; i++) 
			for(j = 0; j < columns; j++) 
				if(b[i][j].animate == FLAG_ON) {
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) + pos, CELL_SIDE * (i + 0.5), CELL_SIDE * (28.0 / 80.0), current->r, current->g, current->b, current->a);
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5), CELL_SIDE * (i + 0.5) + pos, CELL_SIDE * (28.0 / 80.0), current->r, current->g, current->b, current->a);
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5) - pos, CELL_SIDE * (i + 0.5), CELL_SIDE * (28.0 / 80.0), current->r, current->g, current->b, current->a);
					AD_DrawCircle(ren, CELL_SIDE * (j + 0.5), CELL_SIDE * (i + 0.5) - pos, CELL_SIDE * (28.0 / 80.0), current->r, current->g, current->b, current->a);
				}	
		AD_CreateBoard(ren, 255, 255, 255, 0);
		UpdateBoardStatus(ren, b);		
		SDL_Delay(1000 / 60);	
	}
	SDL_RenderClear(*ren);
}

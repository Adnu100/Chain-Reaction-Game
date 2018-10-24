#include <SDL2/SDL.h>
#include "chain.h"

extern int rows, columns;

void START_THE_GAME(board *ADD_b, player **ADD_pl, int players_number, int computer_players_number) {
	const int WINDOW_WIDTH = columns * CELL_SIDE;
	const int WINDOW_HEIGHT = rows * CELL_SIDE + CELL_SIDE * 2;
	SDL_Window *window;
	SDL_Renderer *ren;	
	if(!(window = SDL_CreateWindow("Chain Reaction Game", 100, 100, WINDOW_WIDTH + 2, WINDOW_HEIGHT, SDL_WINDOW_SHOWN))) {
		fprintf(stderr, "Could not Create Window : %s\n", SDL_GetError());
		exit(2);
	}
	if(!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "could not Create Renderer : %s\n", SDL_GetError());
		exit(3);
	}
	int i, j, moves = 0;
	player *pl = *ADD_pl;
	board b = *ADD_b;
	player *current = pl; 
	SDL_Event e;
	STAT gamestat = PLAYING; 
	while(gamestat != OVER) {
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT :
					gamestat = OVER;
					break;
				case SDL_MOUSEBUTTONDOWN :
					if(current->next == current) {
						gamestat = OVER;
						break;
					}	
					if(e.button.x < WINDOW_WIDTH && e.button.y < WINDOW_HEIGHT - CELL_SIDE * 2) { 
						j = e.button.x / CELL_SIDE;
						i = e.button.y / CELL_SIDE;
						if(b[i][j].p == NULL || b[i][j].p == current) {
							advance(b, i, j, current , &ren); 	
							current = current->next;
							if(moves >= players_number + computer_players_number)
								Delete_Out_Players(b, &pl, &current); 		
							moves++;
						}
					}
					break;
				default :
					break;
			}
		}	
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderClear(ren);
		if(current->next == current)
			AD_CreateBoard(&ren, current->r, current->g, current->b, current->a); 	
		else 							
			AD_CreateBoard(&ren, 255, 255, 255, 0);	 	 
		UpdateBoardStatus(&ren, b); 
		SDL_RenderPresent(ren);
		if(current->type != HUMAN) {
				if(current->next != current) { 
					SetMove(b ,current, &i, &j); 
					advance(b, i, j, current, &ren);
					if(moves >= players_number + computer_players_number)
						Delete_Out_Players(b, &pl, &current);
					moves++;
					current = current->next;	
				}	
		}
		SDL_Delay(1000 / 30);
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);	
}


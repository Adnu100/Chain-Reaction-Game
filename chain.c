#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chain.h"

int rows = 5, columns = 5;

int main(int argc, char *argv[]) {	
	int i, j;
	int players_number, computer_players_number, moves = 0;
	board b = NULL;
	player *pl;
	// test scanf
	printf("->Enter Rows, Columns, Player Numbers, Computer Players : ");
	scanf("%d%d%d%d", &rows, &columns, &players_number, &computer_players_number);
	//test ends 
	Initiate_My_Board(&b);
	Initiate_My_Players(&pl, players_number, computer_players_number);
	const int WINDOW_WIDTH = columns * CELL_SIDE;
	const int WINDOW_HEIGHT = rows * CELL_SIDE + CELL_SIDE * 2;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window;
	SDL_Renderer *ren;
	/*window = SDL_CreateWindow("Chain Reaction Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); */
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Could not Initialize SDL : %s\n", SDL_GetError());
		exit(1);
	}	
	if(!(window = SDL_CreateWindow("Chain Reaction Game", 100, 100, WINDOW_WIDTH + 2, WINDOW_HEIGHT, SDL_WINDOW_SHOWN))) {
		fprintf(stderr, "Could not Create Window : %s\n", SDL_GetError());
		exit(2);
	}
	if(!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "could not Create Renderer : %s\n", SDL_GetError());
		exit(3);
	}
	SDL_Event e;
	STAT gamestat = PLAYING;
	player *current = pl, *A_holder = pl; 
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
						//printf("Clicked on Cell [%d][%d]", i, j); //test code
						if(b[i][j].p == NULL || b[i][j].p == current) {
							advance(b, i, j, current , &ren); 	
							current = current->next;
							if(moves >= players_number + computer_players_number)
								Delete_Out_Players(b, &pl, &current); 		
							//printboard(b);
							//printplayer(&pl);
							//printf("\n");
							//printf("current player : %d\n", current->number);
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
					SDL_Delay(500); 
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
	DestroyPlayer(&A_holder);
	DestroyBoard(&b);
	SDL_DestroyWindow(window);	
	SDL_Quit();
	return 0;
}

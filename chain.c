#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chain.h"

int rows = 5, columns = 5;

int main(int argc, char *argv[]) {	
	int players_number, computer_players_number;
	board b = NULL;
	player *pl;
	// test scanf
	printf("->Enter Rows, Columns, Player Numbers, Computer Players : ");
	scanf("%d%d%d%d", &rows, &columns, &players_number, &computer_players_number);
	//test ends 
	Initiate_My_Board(&b);
	player *A_holder = Initiate_My_Players(&pl, players_number, computer_players_number);
	const int WINDOW_WIDTH = columns * CELL_SIDE;
	const int WINDOW_HEIGHT = rows * CELL_SIDE + CELL_SIDE * 2;
	SDL_Window *window;
	SDL_Renderer *ren;
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
	START_THE_GAME(&ren, &b, &pl, players_number, computer_players_number, WINDOW_HEIGHT, WINDOW_WIDTH);
	DestroyPlayer(&A_holder);
	DestroyBoard(&b);
	SDL_DestroyWindow(window);	
	SDL_Quit();
	return 0;
}


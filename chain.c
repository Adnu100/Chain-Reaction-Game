#include <stdio.h>
#include <SDL2/SDL.h>
#include "chain.h"

int rows = 5, columns = 5;

int main(int argc, char *argv[]) {	
	/* Initialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Could not Initialize SDL : %s\n", SDL_GetError());
		exit(1);
	}
	
	int players_number, computer_players_number;
	board b = NULL;
	// test scanf
	printf("->Enter Rows, Columns, Player Numbers, Computer Players : ");
	scanf("%d%d%d%d", &rows, &columns, &players_number, &computer_players_number);
	//test ends 
	Initiate_My_Board(&b);
	player *pl = Create_Player_Row(players_number, computer_players_number), *pl2 = pl;
	
	/* Call a function to start the game */
	START_THE_GAME(&b, &pl, players_number, computer_players_number);
	
	/* Free the malloced Resources */
	DestroyPlayer(&pl2);
	DestroyBoard(&b);
	SDL_Quit();
	return 0;
}



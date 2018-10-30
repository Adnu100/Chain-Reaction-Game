#include <stdio.h>
#include <SDL2/SDL.h>
#include "chain.h"

/* Number of rows and columns will be required at each and every step of game and for each function of the program, so declaring them as Global variables */
int rows, columns;
SDL_Color *ColorRow;

int main(int argc, char *argv[]) {	
	/* Initialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Could not Initialize SDL : %s\n", SDL_GetError());
		exit(1);
	}
	
	/* Declare human players and computer players variables, a board and player row */
	int players_number, computer_players_number;
	board b = NULL;
	player *pl, *pl2;
	  
	/* First ask user whether to start a new game or resume a game. For new game, define table rows, columns, 		 * human and computer players in a window.
	 * Also, ask if user wants to quit.
	 */
	switch(startmenu(&players_number, &computer_players_number)) {
		case QUIT:
			/* we can safely return from here as any memory is not dynamically alloted till this point */
			return 0;
			break;
		case NEW_GAME:
			/* Initiate a board and players row */
			b = Initiate_My_Board();
			pl = Create_Player_Row(players_number, computer_players_number); 
			pl2 = pl;
			break;
		case RESUME:
			//code to extract game information from file	
			break;
		default:
			break;	
	}
	
	/* A variable telling if we need to quit or continue a new game */
	STAT var = PLAYING;
	
	while(var == PLAYING) { 	
		var = OVER;		
		/* Call a function to start the game */
		switch(START_THE_GAME(&b, &pl, players_number, computer_players_number)) {
			case NEW_GAME:	
				/* "goto" can be used (goto the beggining again to restart a new game). 
				 * But sir told goto is bad, so using while loop
				 */
				var = PLAYING;
				DestroyPlayer(&pl2);
				DestroyBoard(&b);
				b = Initiate_My_Board();
			 	pl = Create_Player_Row(players_number, computer_players_number);
			 	pl2 = pl;
			 	break;
			case SAVE:
			 	// code to save the game
			 	break;		
			case QUIT: 
				/* board and player row memory is dynamically alloted. */
				/* So before ending the game program, that memory is needed to free */  
				/* Free the malloced Resources */
				free(ColorRow);
				DestroyPlayer(&pl2);
				DestroyBoard(&b);
				break;	
			default:
				break;		
		}
	}
	/* Quit SDL */
	SDL_Quit();		
	/* Successfully exit the game */
	return 0;
}



#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "chain.h"

/* Number of rows and columns will be required at each and every step of game and for each function of the program, so declaring them as Global variables */
int rows = -1, columns = -1, speed = 4;
SDL_Color *ColorRow = NULL;
player_type difficulty = BOT_MEDIUM;

int main(int argc, char *argv[]) {
	/* Declare human players and computer players variables, a board and player row, also the savefile, 		 *resumefile name and other useful variables
	 */
	board b = NULL;
	player *pl, *pl2, *current;
	int players_number = -1, computer_players_number = -1, moves = 0;
	char *savefile = NULL, *resumefile = NULL;
	int QUICK_START_FLAG = FLAG_OFF, RES_FLAG = FLAG_OFF;
	
	/* process the command line options first */
	int opt, opt_index;
	const struct option optarr[] = {
		{"quick-start", no_argument, NULL, 'q'}, 
		{"help", no_argument, NULL, 'h'}, 
		{"save", required_argument, NULL, 's'}, 
		{"resume-default", no_argument, NULL, 'L'},
		{"slow", no_argument, NULL, '1'},
		{"medium", no_argument, NULL, '2'},
		{"fast", no_argument, NULL, '3'},
		{"super-fast", no_argument, NULL, '4'},
		{"no-animations", no_argument, NULL, 'N'},
		{"resume", required_argument, NULL, 'R'},
		{NULL, 0, NULL, 0}
	};
	while((opt = getopt_long(argc, argv, "r:c:qhH:C:s:R:D:N", optarr, &opt_index)) != -1) {
		switch(opt) {
			case '1':
				speed = 3;
				break;
			case '2':
				speed = 4;
				break;
			case '3':
				speed = 5;
				break;		
			case '4':
				speed = 8;
				break;	
			case 'N':
				speed = -1;
				break;	
			case 'h':
				Display_help();
				return 0;
				break;
			case 'r':
				if(!RES_FLAG) 
					if(atoi(optarg) >= 4)
						rows = atoi(optarg);
				break;
			case 'c':
				if(!RES_FLAG)
					if(atoi(optarg) >= 4)
						columns = atoi(optarg);
				break;
			case 'q':
				QUICK_START_FLAG = FLAG_ON;
				if(rows == -1)
					rows = 5;
				if(columns == -1)
					columns = 5;
				if(players_number == -1)
					players_number = 1;
				if(computer_players_number == -1)
					computer_players_number = 1;
				break;
			case 's':
				savefile = (char *)malloc(sizeof(char) * strlen(optarg) + 7);
				strcpy(savefile, optarg);
				strcat(savefile, ".chain");
				break;
			case 'R':
				if(!RES_FLAG) {
					resumefile = (char *)malloc(sizeof(char) * strlen(optarg) + 1);
					strcpy(resumefile, optarg);		
					QUICK_START_FLAG = FLAG_ON;
					RES_FLAG = FLAG_ON;
					if(ResumeGame(&b, &pl, &pl2, &current, &players_number, &computer_players_number, resumefile, &moves) == OVER)
						return 0;
				}	
				break;	
			case 'H':	
				if(!RES_FLAG) 
					if(atoi(optarg) >= 0)
						players_number = atoi(optarg);
				break;
			case 'C':
				if(!RES_FLAG) 
					if(atoi(optarg) >= 0)
						computer_players_number = atoi(optarg);
				break;
			case 'D':
				if(!RES_FLAG) {
					opt = atoi(optarg); {
					switch(opt) {
						case 1:
							difficulty = BOT_EASIEST_MODE;
							break;
						case 2:
							difficulty = BOT_EASY;
							break;
						case 3:
							difficulty = BOT_MEDIUM;
							break;
						default:
							difficulty = BOT_HARD;
							break;				
						}
					}	
				}	
				break;
			case 'L':
				if(!RES_FLAG) {
					QUICK_START_FLAG = FLAG_ON;
					RES_FLAG = FLAG_ON;
					if(ResumeGame(&b, &pl, &pl2, &current, &players_number, &computer_players_number, resumefile, &moves) == OVER)
						return 0;
				}		
				break;	
			case '?':
				printf("Type %s --help | %s -h for help\n", argv[0], argv[0]);
				exit(7);
				break;							
		}
	}
	if((players_number + computer_players_number < 2) && players_number != -1 && computer_players_number != -1)
		players_number = computer_players_number = 1;

	/* Initialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Could not Initialize SDL : %s\n", SDL_GetError());
		exit(1);
	}
	  
	/* If the user has not given the option "quick-start" or provided game variables then let him set the game 		 * variables, 
	 * First ask user whether to start a new game or resume a game. For new game, define table rows, columns, 		 * human and computer players in a window.
	 * Also, ask if user wants to quit.
	 */
	if(!QUICK_START_FLAG)  
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
				current = pl;
				break;
			case RESUME:
				/* extract the game information from a file into the board and player row */
				if(ResumeGame(&b, &pl, &pl2, &current, &players_number, &computer_players_number, resumefile, &moves) == OVER)
					return 0;	
				break;
			default:
				break;	
		}
	else if(!RES_FLAG) {
		b = Initiate_My_Board();
		pl = Create_Player_Row(players_number, computer_players_number);
		pl2 = pl;
		current = pl;		
	}	
	
	/* A variable telling if we need to quit or continue a new game */
	STAT var = PLAYING;
	
	while(var == PLAYING) { 	
		var = OVER;		
		/* Call a function to start the game */
		switch(START_THE_GAME(&b, &pl, players_number, computer_players_number, &current, &moves)) {
			case NEW_GAME:	
				/* "goto" can be used (goto the beggining again to restart a new game). 
				 * Goto leads to bad and unreadable code, so using while loop
				 */
				var = PLAYING;
				DestroyPlayer(&pl2);
				DestroyBoard(&b);
				b = Initiate_My_Board();
			 	pl = Create_Player_Row(players_number, computer_players_number);
			 	pl2 = pl;
			 	current = pl;
			 	break;
			case SAVE:
				/* save the game into a file */
			 	SaveGame(b, pl2, current, players_number, computer_players_number, savefile, moves);
			 	DestroyPlayer(&pl2);			 	
			 	DestroyBoard(&b);
			 	break;		
			case QUIT:
				/* print the game statistics before exiting (like a standard game) */ 
				if(current->next == current) {
					if(current->type == HUMAN)
						printf("Game status:\n\tTotal Moves Played : %d\n\tTotal Players : %d (%d human, %d bots)\n\tPlayer %d won! Congrats!\n", moves, players_number + computer_players_number, players_number, computer_players_number, current->number);
					else if(players_number != 0)
						printf("Game status:\n\tTotal Moves Played : %d\n\tTotal Players : %d (%d human, %d bots)\n\tPlayer %d won (computer player)\nBetter Luck next time!\n", moves, players_number + computer_players_number, players_number, computer_players_number, current->number);	
					else
						printf("Game status:\n\tTotal Moves Played : %d\n\tTotal Players : %d (%d human, %d bots)\n\tPlayer %d won!\n", moves, players_number + computer_players_number, players_number, computer_players_number, current->number);	
				}
				else 
					printf("Game quit\n");		
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



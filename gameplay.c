#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "chain.h"

extern int rows, columns;

GAME_STATE startmenu(int *players_number, int *computer_players_number) {
	if(TTF_Init()) {
		fprintf(stderr, "Could not Initiate Fonts : %s\n", TTF_GetError());
		exit(4);
	}
	SDL_Window *window;
	SDL_Renderer *ren;
	SDL_Rect R1 = {30, 20, 580, 140}, R2 = {180, 230, 280, 100}, R3 = {180, 400, 280, 100}, R4 = {170, 570, 280, 100}; 
	if(!(window = SDL_CreateWindow("Chain Reaction Game", 100, 100, 640, 800, SDL_WINDOW_SHOWN))) {
		fprintf(stderr, "Could not Create Window : %s\n", SDL_GetError());
		exit(2);
	}
	if(!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "could not Create Renderer : %s\n", SDL_GetError());
		exit(3);
	}
	TTF_Font *SansSherifFont = TTF_OpenFont("font.ttf", 50);
	if(SansSherifFont == NULL) {
		fprintf(stderr, "Could not find the font loader file : %s", TTF_GetError());
		exit(5);
	}
	SDL_Surface *sur;
	SDL_Color Red = {255, 0, 0}, Green = {0, 255, 0}, Blue = {0, 0, 255}, Title_color = {255, 0, 255, 0}, White = {255, 255, 255, 0};
	SDL_Texture *title, *newgame, *resume, *quit;
	sur = TTF_RenderText_Solid(SansSherifFont, "-- Chain Reaction Game --", Title_color);
	title = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "New Game", Blue);
	newgame = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "Resume", Green);
	resume = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "Quit", Red);
	quit = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	int flag = FLAG_ON;
	GAME_STATE Current_Game_state = NONE;
	SDL_Event e;
	while(flag) {
		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					Current_Game_state = QUIT;
					flag = FLAG_OFF;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(e.button.x > 180 && e.button.x < 470) {
						if(e.button.y > 230 && e.button.y < 330)
							Current_Game_state = NEW_GAME;	
						if(e.button.y > 400 && e.button.y < 500)
							Current_Game_state = RESUME;
						if(e.button.y > 570 && e.button.y < 670) {
							Current_Game_state = QUIT;
							SDL_DestroyRenderer(ren);
							SDL_DestroyWindow(window);
							return Current_Game_state;
						}	
						flag = FLAG_OFF;
					}
					break;	
				default:
					break;	
			}
		}
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, title, NULL, &R1);
		SDL_RenderCopy(ren, newgame, NULL, &R2);
		SDL_RenderCopy(ren, resume, NULL, &R3);
		SDL_RenderCopy(ren, quit, NULL, &R4);
		SDL_SetRenderDrawColor(ren, 200, 255, 200, 10);
		SDL_RenderDrawLine(ren, 170, 210, 170, 710);
		SDL_RenderDrawLine(ren, 170, 210, 470, 210);
		SDL_RenderDrawLine(ren, 470, 710, 170, 710);
		SDL_RenderDrawLine(ren, 470, 710, 470, 210);
		SDL_RenderDrawLine(ren, 170, 350, 470, 350);
		SDL_RenderDrawLine(ren, 170, 550, 470, 550);
		SDL_RenderPresent(ren);
		SDL_Delay(1000 / 60);
	}
	SDL_DestroyTexture(newgame);
	SDL_DestroyTexture(resume);
	SDL_DestroyTexture(quit);
	SDL_Texture *choose, *human, *computer, *count_row, *count_col, *p, *m;
	sur = TTF_RenderText_Solid(SansSherifFont, "Players : ", Blue);
	human = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "Computer Players : ", Blue);
	computer = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "Rows : ", Blue);
	count_row = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "Columns : ", Blue);
	count_col = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "START GAME", Blue);
	choose = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	char plus[2] = "+", minus[2] = "-";	
	sur = TTF_RenderText_Solid(SansSherifFont, plus, Green);
	p = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, minus, Red);
	m = SDL_CreateTextureFromSurface(ren, sur);	
	SDL_FreeSurface(sur);
	char numbers[20][3];
	int i, i1 = 1, i2 = 1, i3 = 5, i4 = 5, x, y;
	for(i = 0; i < 10; i++) {
		numbers[i][0] = '0' + i;
		numbers[i][1] = '\0';
	}	
	for(i = 0; i < 10; i++) {
		numbers[10 + i][0] = '1';
		numbers[10 + i][1] = '0' + i;
		numbers[10 + i][2] = '\0';
	}
	SDL_Texture *numpad[20];
	for(i = 0; i < 20; i++) {
		sur = TTF_RenderText_Solid(SansSherifFont, numbers[i], White);
		numpad[i] = SDL_CreateTextureFromSurface(ren, sur);
		SDL_FreeSurface(sur);
	}
	/* Declaring this much variables will consume space but will reduce time complexity */
	SDL_Rect R11 = {10, 200, 180, 80}, R12 = {10, 300, 180, 80}, R13 = {10, 400, 180, 80}, R14 = {10, 500, 180, 80}, R15 = {180, 620, 280, 160}, R21 = {210, 200, 80, 80}, R22 = {320, 200, 80, 80}, R23 = {430, 200, 80, 80}, R31 = {210, 300, 80, 80}, R32 = {320, 300, 80, 80}, R33 = {430, 300, 80, 80}, R41 = {210, 400, 80, 80}, R42 = {320, 400, 80, 80}, R43 = {430, 400, 80, 80}, R51 = {210, 500, 80, 80}, R52 = {320, 500, 80, 80}, R53 = {430, 500, 80, 80}; 
	flag = FLAG_ON;
	if(Current_Game_state == NEW_GAME) {
		while(flag) {
			if(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:
						flag = FLAG_OFF;
						break;
					case SDL_MOUSEBUTTONDOWN:
						x = e.button.x;
						y = e.button.y;
						if(x > R21.x && x < R21.x + R21.w && y > R21.y && y < R21.y + R21.h) {
							if(i1 != 0)
								i1--;
						}		
						else if(x > R23.x && x < R23.x + R23.w && y > R23.y && y < R23.y + R23.h) {
							if(i1 != 19)
								i1++;
						}		
						else if(x > R31.x && x < R31.x + R31.w && y > R31.y && y < R31.y + R31.h) {
							if(i2 != 0)
								i2--;
						}		
						else if(x > R33.x && x < R33.x + R33.w && y > R33.y && y < R33.y + R33.h) {
							if(i2 != 19)
								i2++;
						}		
						else if(x > R41.x && x < R41.x + R41.w && y > R41.y && y < R41.y + R41.h) {
							if(i3 != 4)
								i3--;
						}		
						else if(x > R43.x && x < R43.x + R43.w && y > R43.y && y < R43.y + R43.h) {
							if(i3 != 19)
								i3++;
						}		
						else if(x > R51.x && x < R51.x + R51.w && y > R51.y && y < R51.y + R51.h) {
							if(i4 != 4)
								i4--;
						}		
						else if(x > R53.x && x < R53.x + R53.w && y > R53.y && y < R53.y + R53.h) {
							if(i4 != 19)
								i4++;		
						}
						else if(x > R15.x && x < R15.x + R15.w && y > R15.y && y < R15.y + R15.h) {
							if(i1 + i2 >= 2)
								flag = FLAG_OFF;
						}
						break;	
					default:
						break;
				}
			}	
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, p, NULL, &R23);
			SDL_RenderCopy(ren, p, NULL, &R33);
			SDL_RenderCopy(ren, p, NULL, &R43);
			SDL_RenderCopy(ren, p, NULL, &R53);
			SDL_RenderCopy(ren, m, NULL, &R21);
			SDL_RenderCopy(ren, m, NULL, &R31);
			SDL_RenderCopy(ren, m, NULL, &R41);
			SDL_RenderCopy(ren, m, NULL, &R51);
			SDL_RenderCopy(ren, numpad[i1], NULL, &R22);
			SDL_RenderCopy(ren, numpad[i2], NULL, &R32);
			SDL_RenderCopy(ren, numpad[i3], NULL, &R42);
			SDL_RenderCopy(ren, numpad[i4], NULL, &R52);
			SDL_RenderCopy(ren, title, NULL, &R1);
			SDL_RenderCopy(ren, human, NULL, &R11);
			SDL_RenderCopy(ren, computer, NULL, &R12);
			SDL_RenderCopy(ren, count_row, NULL, &R13);
			SDL_RenderCopy(ren, count_col, NULL, &R14);
			SDL_RenderCopy(ren, choose, NULL, &R15);
			SDL_SetRenderDrawColor(ren, 150, 255, 150, 0);
			SDL_RenderDrawRect(ren, &R21);
			SDL_RenderDrawRect(ren, &R22);
			SDL_RenderDrawRect(ren, &R23);
			SDL_RenderDrawRect(ren, &R31);
			SDL_RenderDrawRect(ren, &R32);
			SDL_RenderDrawRect(ren, &R33);
			SDL_RenderDrawRect(ren, &R41);
			SDL_RenderDrawRect(ren, &R42);
			SDL_RenderDrawRect(ren, &R43);
			SDL_RenderDrawRect(ren, &R51);
			SDL_RenderDrawRect(ren, &R52);
			SDL_RenderDrawRect(ren, &R53);
			SDL_RenderDrawRect(ren, &R15);
			SDL_RenderPresent(ren);
			SDL_Delay(1000 / 60);
		}
	}
	for(i = 0; i < 20; i++)
		SDL_DestroyTexture(numpad[i]);
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(p);
	SDL_DestroyTexture(m);
	SDL_DestroyTexture(human);
	SDL_DestroyTexture(computer);
	SDL_DestroyTexture(count_row);
	SDL_DestroyTexture(count_col);
	SDL_DestroyTexture(choose);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	*players_number = i1;
	*computer_players_number = i2;
	rows = i3;
	columns = i4;
	return Current_Game_state;
}

void START_THE_GAME(board *b, player **pl, int players_number, int computer_players_number) {
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
	player *current = *pl; 
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
						if((*b)[i][j].p == NULL || (*b)[i][j].p == current) {
							advance(*b, i, j, current , &ren); 	
							current = current->next;
							if(moves >= players_number + computer_players_number)
								Delete_Out_Players(*b, pl, &current); 		
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
		UpdateBoardStatus(&ren, *b); 
		SDL_RenderPresent(ren);
		if(current->type != HUMAN) {
				if(current->next != current) { 
					SetMove(*b ,current, &i, &j); 
					advance(*b, i, j, current, &ren);
					if(moves >= players_number + computer_players_number)
						Delete_Out_Players(*b, pl, &current);
					moves++;
					current = current->next;	
				}	
		}
		SDL_Delay(1000 / 30);
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);	
}


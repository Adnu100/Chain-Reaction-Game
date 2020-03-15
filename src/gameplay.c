#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chain.h>

extern int rows, columns;
extern player_type difficulty;
extern SDL_Color *ColorRow;
extern char *TTF_PATH;

int center;
TTF_Font *SansSherifFont;
SDL_Rect Rect1, Rect2;
SDL_Texture *savegame, *create_new_game;

SDL_Color Red = {255, 0, 0}, Green = {0, 255, 0}, Blue = {0, 0, 255}, Title_color = {255, 0, 255, 0}, White = {255, 255, 255, 0};

/* TTF initializer function */
void TTF_Initialize_All(void) {
	static int isinit = FLAG_ON;
	if(isinit) {
		if(TTF_Init()) {
			fprintf(stderr, "Could not Initiate Fonts : %s\n", TTF_GetError());
			exit(4);
		}
		if(TTF_PATH == NULL)
			SansSherifFont = TTF_OpenFont("support/font.ttf", 50);
		else
			SansSherifFont = TTF_OpenFont(TTF_PATH, 50);
		if(SansSherifFont == NULL) {
			fprintf(stderr, "Could not find the font loader file : %s\n", TTF_GetError());
			exit(5);
		}
	}
	isinit = FLAG_OFF;	
}

/* The GUI-type Startmenu, will not be used when quick start */
GAME_STATE startmenu(int *players_number, int *computer_players_number) {
	TTF_Initialize_All();
	SDL_Window *window;
	SDL_Renderer *ren;
	SDL_Rect R1 = {30, 20, 580, 140}, R2 = {180, 230, 280, 100}, R3 = {180, 400, 280, 100}, R4 = {170, 570, 280, 100};
	SDL_Rect T = {30, 720, 580, 20}, Diff1 = {30, 750, 145, 50}, Diff2 = {175, 750, 145, 50}, Diff3 = {320, 750, 145, 50}, Diff4 = {465, 750, 145, 50};
	if(!(window = SDL_CreateWindow("Chain Reaction Game", 100, 100, 640, 800, SDL_WINDOW_SHOWN))) {
		fprintf(stderr, "Could not Create Window : %s\n", SDL_GetError());
		exit(2);
	}
	if(!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "could not Create Renderer : %s\n", SDL_GetError());
		exit(3);
	}
	int redraw = 1;
	SDL_Surface *sur;
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
	GAME_STATE Current_Game_state = NEW_GAME;
	SDL_Event e;
	SDL_Texture *tex1, *tex2, *tex3, *tex4, *th;
	sur = TTF_RenderText_Solid(SansSherifFont, "_Computer Player Difficulty Level_", Title_color);
	th = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "1", White);
	tex1 = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "2", White);
	tex2 = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "3", White);
	tex3 = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "4", White);
	tex4 = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	if(rows == -1 && columns == -1 && *players_number == -1 && *computer_players_number == -1)
		while(flag) {
			if(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:
						Current_Game_state = QUIT;
						flag = FLAG_OFF;
						break;
					case SDL_MOUSEBUTTONDOWN:
						if(e.button.x > 180 && e.button.x < 470) {
							if(e.button.y > 230 && e.button.y < 330) {
								Current_Game_state = NEW_GAME;	
								flag = FLAG_OFF;
							}	
							if(e.button.y > 400 && e.button.y < 500) {
								Current_Game_state = RESUME;
								SDL_DestroyRenderer(ren);
								SDL_DestroyWindow(window);
								flag = FLAG_OFF;
								return Current_Game_state;
							}	
							if(e.button.y > 570 && e.button.y < 670) {
								Current_Game_state = QUIT;
								SDL_DestroyRenderer(ren);
								SDL_DestroyWindow(window);
								flag = FLAG_OFF;
								return Current_Game_state;
							}	
						}
						redraw = difficulty;
						if(e.button.x > Diff1.x && e.button.y > Diff1.y && e.button.x < Diff1.x + Diff1.w && e.button.y < Diff1.y + Diff1.h)
							difficulty = BOT_EASIEST_MODE;
						else if(e.button.x > Diff2.x && e.button.y > Diff2.y && e.button.x < Diff2.x + Diff2.w && e.button.y < Diff2.y + Diff2.h)
							difficulty = BOT_EASY;
						else if(e.button.x > Diff3.x && e.button.y > Diff3.y && e.button.x < Diff3.x + Diff3.w && e.button.y < Diff3.y + Diff3.h)
							difficulty = BOT_MEDIUM;
						else if(e.button.x > Diff4.x && e.button.y > Diff4.y && e.button.x < Diff4.x + Diff4.w && e.button.y < Diff4.y + Diff4.h)
							difficulty = BOT_HARD;	
						if(redraw != difficulty)
							redraw = 1;
						else
							redraw = 0;
						break;	
					default:
						break;	
				}
			}
			if(redraw == 1) {
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, title, NULL, &R1);
				SDL_RenderCopy(ren, newgame, NULL, &R2);
				SDL_RenderCopy(ren, resume, NULL, &R3);
				SDL_RenderCopy(ren, quit, NULL, &R4);
				SDL_RenderCopy(ren, th, NULL, &T);
				SDL_RenderCopy(ren, tex1, NULL, &Diff1);
				SDL_RenderCopy(ren, tex2, NULL, &Diff2);
				SDL_RenderCopy(ren, tex3, NULL, &Diff3);
				SDL_RenderCopy(ren, tex4, NULL, &Diff4);
				SDL_SetRenderDrawColor(ren, 200, 255, 200, 10);
				SDL_RenderDrawLine(ren, 170, 210, 170, 710);
				SDL_RenderDrawLine(ren, 170, 210, 470, 210);
				SDL_RenderDrawLine(ren, 470, 710, 170, 710);
				SDL_RenderDrawLine(ren, 470, 710, 470, 210);
				SDL_RenderDrawLine(ren, 170, 350, 470, 350);
				SDL_RenderDrawLine(ren, 170, 550, 470, 550);
				SDL_RenderDrawRect(ren, &Diff1);
				SDL_RenderDrawRect(ren, &Diff2);
				SDL_RenderDrawRect(ren, &Diff3);
				SDL_RenderDrawRect(ren, &Diff4);
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
				switch(difficulty) {
					case BOT_EASIEST_MODE:
						SDL_RenderDrawRect(ren, &Diff1);
						break;
					case BOT_EASY:
						SDL_RenderDrawRect(ren, &Diff2);
						break;
					case BOT_MEDIUM:
						SDL_RenderDrawRect(ren, &Diff3);
						break;
					default:
						SDL_RenderDrawRect(ren, &Diff4);
						break;			
				}
				SDL_RenderPresent(ren);
				redraw = 0;
			}
		}
	SDL_DestroyTexture(newgame);
	SDL_DestroyTexture(resume);
	SDL_DestroyTexture(quit);
	if(Current_Game_state == NEW_GAME) {
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
		if(*players_number != -1)
			i1 = *players_number;
		if(*computer_players_number != -1)	
			i2 = *computer_players_number;
		if(rows != -1)	
			i3 = rows;
		if(columns != -1)	
			i4 = columns;
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
		redraw = 1;
		while(flag) {
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:
						flag = FLAG_OFF;
						return QUIT;
						break;
					case SDL_MOUSEBUTTONDOWN:
						x = e.button.x;
						y = e.button.y;
						if(x > R21.x && x < R21.x + R21.w && y > R21.y && y < R21.y + R21.h) {
							if(i1 != 0)
								if(*players_number == -1)
									i1--;
						}		
						else if(x > R23.x && x < R23.x + R23.w && y > R23.y && y < R23.y + R23.h) {
							if(i1 != 19)
								if(*players_number == -1)
									i1++;
						}		
						else if(x > R31.x && x < R31.x + R31.w && y > R31.y && y < R31.y + R31.h) {
							if(i2 != 0)
								if(*computer_players_number == -1)
									i2--;
						}		
						else if(x > R33.x && x < R33.x + R33.w && y > R33.y && y < R33.y + R33.h) {
							if(i2 != 19)
								if(*computer_players_number == -1)
									i2++;
						}		
						else if(x > R41.x && x < R41.x + R41.w && y > R41.y && y < R41.y + R41.h) {
							if(i3 != 4)
								if(rows == -1)
									i3--;
						}		
						else if(x > R43.x && x < R43.x + R43.w && y > R43.y && y < R43.y + R43.h) {
							if(i3 != 19)
								if(rows == -1)
									i3++;
						}		
						else if(x > R51.x && x < R51.x + R51.w && y > R51.y && y < R51.y + R51.h) {
							if(i4 != 4)
								if(columns == -1)
									i4--;
						}		
						else if(x > R53.x && x < R53.x + R53.w && y > R53.y && y < R53.y + R53.h) {
							if(i4 != 19)
								if(columns == -1)
									i4++;		
						}
						else if(x > R15.x && x < R15.x + R15.w && y > R15.y && y < R15.y + R15.h) {
							if(i1 + i2 >= 2)
								flag = FLAG_OFF;
						}
						redraw = 1;
						break;	
					default:
						break;
				}
			}
			if(redraw == 1) {	
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
				redraw = 0;
			}
		}
		ColorRow = (SDL_Color *)malloc(sizeof(SDL_Color) * (i1 + i2));
		for(i = 0; i < 20; i++)
			SDL_DestroyTexture(numpad[i]);
		SDL_DestroyTexture(p);
		SDL_DestroyTexture(m);
		SDL_DestroyTexture(human);
		SDL_DestroyTexture(computer);
		SDL_DestroyTexture(count_row);
		SDL_DestroyTexture(count_col);
		SDL_DestroyTexture(choose);
		flag = 1;
		int ci, xi, yi, hueset = 0;
		char line[32] = "Choose player - 1 color :";
		sur = TTF_RenderText_Solid(SansSherifFont, line, White);
		choose = SDL_CreateTextureFromSurface(ren, sur);
		SDL_FreeSurface(sur);
		R2.x = 10;
		R2.y -= 80;
		R2.w += 10;
		SDL_Rect GO_Rect = {R2.x + R2.w + R2.h + 10, R2.y, 100, 100};
		SDL_Texture *Go_tex;
		sur = TTF_RenderText_Solid(SansSherifFont, "Select", White);
		Go_tex = SDL_CreateTextureFromSurface(ren, sur);
		SDL_FreeSurface(sur);
		SDL_Color choosed = {255, 0, 0};
		redraw = 1;
		for(ci = 0; ci < i1 + i2; ) {
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:
						return QUIT;
						break;
					case SDL_MOUSEBUTTONDOWN:
						redraw = 1;
						x = e.button.x;
						y = e.button.y;
						if(x > R2.x && x < (R2.x + 255 * 2) && y > R2.y + R2.h && y < (R2.y + R2.h + 255 * 2)) {
							choosed.r = (x - R2.x) / 2;
							choosed.g = (y - R2.y - R2.h) / 2;
							choosed.b = hueset;
						}
						else if(x > (R2.x + 270 * 2) && x < (R2.x + 270 * 2 + 40) && y > (R2.y + R2.h) && y < (R2.y + R2.h + 255 * 2))
							hueset = (y - (R2.y + R2.h)) / 2;
						else if(x > GO_Rect.x && x < GO_Rect.x + GO_Rect.w && y > GO_Rect.y && y < GO_Rect.y + GO_Rect.h) {
							ColorRow[ci] = choosed;	
							ci++;
							sprintf(line, "Choose player - %d color :", ci + 1);
							SDL_DestroyTexture(choose);
							sur = TTF_RenderText_Solid(SansSherifFont, line, White);
							choose = SDL_CreateTextureFromSurface(ren, sur);
							SDL_FreeSurface(sur);
							choosed.r = Random(0, 255);
							choosed.g = Random(0, 255);
							choosed.b = Random(0, 255);
							hueset = Random(0, 255);
						}
						break;	
				}		
			}
			if(redraw == 1) {
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
				SDL_RenderClear(ren);
				for(xi = 0; xi < 255 * 2; xi++)
					for(yi = 0; yi < 255 * 2; yi++) {
						SDL_SetRenderDrawColor(ren, xi / 2, yi / 2, hueset, 0);
						SDL_RenderDrawPoint(ren, R2.x + xi, R2.y + R2.h + yi);
					}
				SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);	
				for(yi = 0, xi = 250; yi < 255 * 2; yi++, xi -= 0.5) {
					if(xi < 0)
						xi = 0;
					SDL_SetRenderDrawColor(ren, 0, 0, yi / 2, xi);
					SDL_RenderDrawLine(ren, R2.x + 270 * 2, R2.y + R2.h + yi, R2.x + 270 * 2 + 40, R2.y + R2.h + yi);
				}	
				AD_DrawCircle(&ren, R2.x + R2.w + R2.h / 2, R2.y + R2.h / 2, R2.h / 2 - 10, choosed.r, choosed.g, choosed.b, 0);	
				SDL_RenderCopy(ren, title, NULL, &R1);	
				SDL_RenderCopy(ren, choose, NULL, &R2);	
				SDL_RenderCopy(ren, Go_tex, NULL, &GO_Rect);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
				SDL_RenderDrawRect(ren, &GO_Rect);
				SDL_RenderPresent(ren);
				redraw = 0;
			}
		}
		*players_number = i1;
		*computer_players_number = i2;
		rows = i3;
		columns = i4;
	}
	SDL_DestroyTexture(title);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	return Current_Game_state;
}

/* Actual game interface */
GAME_STATE START_THE_GAME(board *b, player **pl, int players_number, int computer_players_number, player **current, int *moves) {
	TTF_Initialize_All();
	if(computer_players_number > 0)
		ComputerPlayerMemoryMalloc();
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
	SDL_Surface *sur;
	sur = TTF_RenderText_Solid(SansSherifFont, "SAVE", Green);
	savegame = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	sur = TTF_RenderText_Solid(SansSherifFont, "NEW GAME", Red);
	create_new_game = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	if(columns % 2 == 0) 
		center = CELL_SIDE * (columns / 2);
	else 
		center = CELL_SIDE * (columns / 2) + CELL_SIDE / 2;	
	Rect1.x = center - 2 * CELL_SIDE;
	Rect2.x = Rect1.x + 2 * CELL_SIDE + CELL_SIDE / 2;
	Rect1.y = Rect2.y = CELL_SIDE * rows + CELL_SIDE / 2;
	Rect1.w = Rect2.w = CELL_SIDE + CELL_SIDE / 2;
	Rect1.h = Rect2.h = CELL_SIDE;
	int i, j, Moves = *moves; 
	SDL_Event e;
	STAT gamestat = PLAYING; 
	unsigned int ticks, tempticks;
	while(gamestat != OVER) {
		ticks = SDL_GetTicks();
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT :
					gamestat = OVER;
					break;
				case SDL_MOUSEBUTTONDOWN :
					i = e.button.x;
					j = e.button.y;
					if(i > Rect1.x && i < Rect1.x + Rect1.w && j > Rect1.y && j < Rect1.y + Rect1.h) {
						SDL_DestroyRenderer(ren);
						SDL_DestroyWindow(window);
						TTF_CloseFont(SansSherifFont);
						TTF_Quit();
						*moves = Moves;
						return SAVE;
					}
					if(i > Rect2.x && i < Rect2.x + Rect2.w && j > Rect2.y && j < Rect2.y + Rect2.h) {
						SDL_DestroyRenderer(ren);
						SDL_DestroyWindow(window);
						*moves = 0;
						return NEW_GAME;
					}	
					if((*current)->next == (*current)) {
						gamestat = OVER;
						break;
					}
					if((*current)->type == HUMAN) {	
						if(e.button.x < WINDOW_WIDTH && e.button.y < WINDOW_HEIGHT - CELL_SIDE * 2) { 
							j = e.button.x / CELL_SIDE;
							i = e.button.y / CELL_SIDE;
							if((*b)[i][j].p == NULL || (*b)[i][j].p == (*current)) {
								tempticks = ticks;
								advance(*b, i, j, (*current) , &ren); 	
								ticks = tempticks;
								(*current) = (*current)->next;
								if(Moves >= players_number + computer_players_number)
									Delete_Out_Players(*b, pl, &(*current)); 		
								Moves++;
							}
							break;
						}
					}	
					break;
				default :
					break;
			}
		}	
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderClear(ren);
		if((*current)->next == (*current))
			AD_CreateBoard(&ren, (*current)->r, (*current)->g, (*current)->b, (*current)->a); 	
		else 							
			AD_CreateBoard(&ren, 255, 255, 255, 0);	 	 
		UpdateBoardStatus(&ren, *b); 
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
		SDL_RenderCopy(ren, savegame, NULL, &Rect1);
		SDL_RenderCopy(ren, create_new_game, NULL, &Rect2);
		SDL_RenderDrawRect(ren, &Rect1);
		SDL_RenderDrawRect(ren, &Rect2);
		AD_DrawCircle(&ren, center, Rect1.y + CELL_SIDE / 2, CELL_SIDE / 2 - CELL_SIDE /10, (*current)->r, (*current)->g, (*current)->b, (*current)->a);
		ticks = SDL_GetTicks() - ticks;
		if(ticks < 22)
			SDL_Delay(22 - ticks);
		SDL_RenderPresent(ren);
		if((*current)->type != HUMAN) {
				if((*current)->next != (*current)) {
					SetMove(*b , (*current), &i, &j);
					advance(*b, i, j, (*current), &ren);
					(*current) = (*current)->next;
					if(Moves >= players_number + computer_players_number)
						Delete_Out_Players(*b, pl, &(*current));
					Moves++;	
				}	
		}
	}
	*moves = Moves;
	if(computer_players_number > 0)
		ComputerPlayerMemoryFree();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	TTF_CloseFont(SansSherifFont);
	TTF_Quit();
	return QUIT;
}


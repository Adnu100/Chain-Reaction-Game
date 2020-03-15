#include <SDL2/SDL.h>
#include "bucket.h"

/* Give -DCELL_SIDE option while compiling to configure the CELL_SIDE
 * in the game.
 * (Add -DCELL_SIDE=side_length to the CFLAGS in the Makefile where 
 * side_length is any number)
 * This will result in bigger or smaller board but may affect
 * performance. Original value is prefered, however can be changed 
 * depending the computer monitor screen you are using 
 */
#ifndef CELL_SIDE 
#define CELL_SIDE 70
#endif

#define FLAG_OFF 0
#define FLAG_ON 1

/* Important Enumerations */
typedef enum STAT {PLAYING, OVER} STAT;		//game stat boolean
typedef enum player_type {HUMAN, BOT_EASIEST_MODE, BOT_EASY, BOT_MEDIUM, BOT_HARD} player_type;
											//player type 
typedef enum GAME_STATE {NEW_GAME, RESUME, SAVE, QUIT, NONE} GAME_STATE;	
											//state of current game

/* A structure containing player information */
typedef struct player {
	int number;
	player_type type;
	int r, g, b, a;
	struct player *next;
} player;	

/* A unit cell containing information about capacity of balls 
 * it can carry, number of balls and the pointer to player 
 * which holds the position of that cell */
struct cell {
	int balls;
	int capacity;
	player *p;
};


/* Board is a 2 * 2 grid of cells */
typedef struct cell **board;	

/* game initializer function */
GAME_STATE START_THE_GAME(board *ADD_b, player **ADD_pl, int players_number, int computer_players_number, player **current, int *moves);
GAME_STATE startmenu(int *players_number, int *computer_players_number);

/* function declarations */
board Initiate_My_Board(void);
player *Create_Player_Row(int players_number, int computer_players_number);
void advance(board b, int i, int j, player *current, SDL_Renderer **ren);
void Delete_Out_Players(board b, player **grid, player **current_player_address);
void AD_CreateBoard(SDL_Renderer **ren, int r, int g, int b, int a);
void UpdateBoardStatus(SDL_Renderer **ren, board b);
void DestroyPlayer(player **pl_add);
void DestroyBoard(board *b);
void AD_DrawCircle(SDL_Renderer **ren, float x, float y, float radius, int r, int g, int b, int a);
void AD_AnimateScreen(SDL_Renderer **ren, board b, player *current, bucket *buc);
void ComputerPlayerMemoryMalloc(void);
void ComputerPlayerMemoryFree(void);
void SetMove(board b, player *current, int *i, int *j);
int Random(int Range_Start, int Range_End);
void SaveGame(board b, player *pl, player *current, int players_number, int computer_players_number, char *filename, int moves);
void ShowSavedGames(void);
STAT ResumeGame(board *b, player **pl, player **playerstore, player **current, int *players_number, int *computer_players_number, char *filename, int *moves);
void TTF_Initialize_All(void);
void Display_help(void);


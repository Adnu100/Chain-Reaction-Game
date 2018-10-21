#define CELL_SIDE 70

#define FLAG_OFF 0
#define FLAG_ON 1

typedef enum STAT {PLAYING, OVER} STAT;
typedef enum player_type {HUMAN, BOT_EASIEST_MODE, BOT_EASY, BOT_MEDIUM, BOT_HARD, NIGHTMARE} player_type;

/* A structure containing player information */
typedef struct player {
	int number;
	player_type type;
	int r, g, b, a;
	struct player *next;
} player;	

/* A unit cell containing information about capacity of balls it can carry, number of balls and the pointer to player which holds the position of that cell */
struct cell {
	int balls;
	int capacity;
	player *p;
	int animate;
};


/* Board is a 2 * 2 grid of cells */
typedef struct cell **board;	

/* function declarations */
void Initiate_My_Board(board *b);
void Initiate_My_Players(player **pl, int players_number, int computer_players_number);
void advance(board b, int i, int j, player *current, SDL_Renderer **ren);
void Delete_Out_Players(board b, player **grid, player **current_player_address);
void AD_CreateBoard(SDL_Renderer **ren, int r, int g, int b, int a);
void UpdateBoardStatus(SDL_Renderer **ren, board b);
void DestroyPlayer(player **pl_add);
void DestroyBoard(board *b);
void AD_DrawCircle(SDL_Renderer **ren, float x, float y, float radius, int r, int g, int b, int a);
void AD_AnimateScreen(SDL_Renderer **ren, board b, player *current);
void SetMove(board b, player *current, int *i, int *j);

/*unuseful functions used for checking neat gameplay and bug fixes */
void printboard(board b);
void printplayer(player **p);

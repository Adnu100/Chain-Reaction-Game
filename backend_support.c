#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chain.h"

extern int rows, columns;
extern SDL_Color *ColorRow;

board Initiate_My_Board(void) {
	int i, j;
	board b = (struct cell **)malloc(sizeof(struct cell *) * rows);
	if(b == NULL) {
		printf("Not Enough Ram!!!\n");
		exit(4);
	}	
	for(i = 0; i < rows; i++) {
		b[i] = (struct cell *)malloc(sizeof(struct cell) * columns);
		if(b[i] == NULL) {
			printf("Not Enough Ram!!!\n");
			exit(4);
		}	
		for(j = 0; j < columns; j++) {
			b[i][j].balls = 0;
			b[i][j].p = NULL;
			if(i == 0 || i == (rows - 1)) {
				if(j == 0 || j == (columns - 1))
					b[i][j].capacity = 1;
				else
					b[i][j].capacity = 2;
			}
			else if(j == 0 || j == (columns - 1)) 
				b[i][j].capacity = 2;
			else 
				b[i][j].capacity = 3;
		}			
	}
	return b;
}	

player *Create_Player_Row(int players_number, int computer_players_number) {
	int i;
	player *pl = (player *)malloc(sizeof(player) * (players_number + computer_players_number));
	if(pl == NULL) {
		printf("Not Enough Ram!!!\n");
			exit(4);
	}
	for(i = 0; i < (players_number + computer_players_number); i++) {
		pl[i].number = i + 1;
		pl[i].r = ColorRow[i].r;
		pl[i].g = ColorRow[i].g;
		pl[i].b = ColorRow[i].b;
		pl[i].a = 0;
		if(i != players_number + computer_players_number - 1)
			pl[i].next = &pl[i + 1];
		else
			pl[i].next = &pl[0];
		if(i < players_number)
			pl[i].type = HUMAN;
		else
			pl[i].type = BOT_HARD;			
	}
	return pl;
}

void advance(board b, int i, int j, player *current, SDL_Renderer **ren) {
	int x, y, flag = FLAG_OFF, flag2 = FLAG_OFF, flag3 = FLAG_ON;
	int Game_terminator = FLAG_OFF;
	bucket buc, CTA;
	buffer B;
	binit(&buc);
	binit(&CTA);
	/*
	 *      Another Method to do this. Renderer not needed. Fast; But animation not supported.	
	 *	
	 *	if(b[i][j].balls == b[i][j].capacity) {
	 *		b[i][j].balls = 0;
	 *		b[i][j].p = NULL;
	 *		b[i][j].wave = wave;
	 *		if(i != 0) 
	 *			advance(b, i - 1, j, current);
	 *		if(i != rows - 1) 
	 *			advance(b, i + 1, j, current);
	 *		if(j != 0) 
	 *			advance(b, i, j - 1, current);
	 *		if(j != columns - 1) 
	 *			advance(b, i, j + 1, current);
	 *	}
	 *	else {
	 *		b[i][j].p = current;	
	 *		b[i][j].balls++;
	 *	}
	 */
	b[i][j].p = current; 
	b[i][j].balls++;
	while(flag3) {
		if(Game_terminator)
			break;
		else {
			flag = flag2 = FLAG_OFF;
			for(x = 0; x < rows && flag == FLAG_OFF; x++) {
				for(y = 0; y < columns && flag == FLAG_OFF; y++) {
					if(b[x][y].p != current && b[x][y].p != NULL)
						flag = FLAG_ON;
					if(b[x][y].balls == 3)
						flag2 = FLAG_ON;	
					if(x == (rows - 1) && y == (columns - 1) && flag2) 
						Game_terminator = FLAG_ON;	
				}
			if(b[rows - 1][columns - 1].p != current && b[rows - 1][columns - 1].p != NULL)
				Game_terminator = FLAG_OFF;			
			}		
			flag3 = FLAG_OFF;
			for(x = 0; x < rows; x++)
				for(y = 0; y < columns; y++) {
					if(b[x][y].balls > b[x][y].capacity) {
						flag3 = FLAG_ON;
						if(x != 0) {
							B.x = x - 1;
							B.y = y;
							addCell(&CTA, B);
						}	
						if(x != rows - 1) {
							B.x = x + 1;
							B.y = y;
							addCell(&CTA, B);
						}	
						if(y != 0) {
							B.x = x;
							B.y = y - 1;
							addCell(&CTA, B);
						}		
						if(y != columns - 1) {
							B.x = x;
							B.y = y + 1;
							addCell(&CTA, B);
						}
						B.x = x;
						B.y = y;
						addCell(&buc, B);
						b[x][y].balls -= (b[x][y].capacity + 1);
					}	
					if(b[x][y].balls == 0) 
						b[x][y].p = NULL;	
				}	
			AD_AnimateScreen(ren, b, current, &buc);		
			for(x = 0; x < storage(&CTA); x++) {
				B = check(&CTA, x);
				b[B.x][B.y].balls++;
				b[B.x][B.y].p = current;
			}
			destroyBucket(&buc);
			destroyBucket(&CTA);
		}	
	}	
}		

void Delete_Out_Players(board b, player **grid, player **current_player_address) {	
	player *temp, *temp2, *temp3;
	temp = temp2 = *grid;
	int i, j, count, flag = 0;
	while(temp2->next != *grid)
		temp2 = temp2->next;
	temp3 = temp2;	
	do {
		if(temp == temp3)
			flag++;
		for(i = 0, count = 0; (i < rows) && (count == 0); i++)
			for(j = 0; j < columns; j++)
				if(b[i][j].p == temp) {
					count++;
					break;	
				}		
		if(!(count)) {
			if(temp == *current_player_address)
				*current_player_address = (*current_player_address)->next;
			temp2->next = temp->next;
			if(temp == *grid)
				*grid = temp->next;
		}
		temp2 = temp;
		temp = temp->next;			
	} while(!(flag));
}	

STAT ResumeGame(board *b, player **pl, player **playerstore, player **current, int *players_number, int *computer_players_number, char *filename) {
	int fd;
	int flag = FLAG_OFF;
	if(filename == NULL) {
		filename = (char *)malloc(sizeof(char) * 20);
		strcpy(filename, "savedgame1.chain");
		flag = FLAG_ON;
	}	
	fd = open(filename, O_RDONLY);
	if(flag == FLAG_ON)
		free(filename);
	if(fd == -1) 
		return OVER;
	read(fd, &rows, sizeof(int));
	read(fd, &columns, sizeof(int));
	read(fd, players_number, sizeof(int));
	read(fd, computer_players_number, sizeof(int));
	lseek(fd, 1, SEEK_CUR);
	int i, j;
	ColorRow = (SDL_Color *)malloc(sizeof(SDL_Color) * (*players_number + *computer_players_number));
	for(i = 0; i < *players_number + *computer_players_number; i++)
		read(fd, &(ColorRow[i]), sizeof(SDL_Color));
	lseek(fd, 1, SEEK_CUR);	
	*b = Initiate_My_Board();
	*pl = Create_Player_Row(*players_number, *computer_players_number);
	*playerstore = *pl;
	int connection, s;
	char type[4];
	for(i = 0; i < *players_number + *computer_players_number; i++) {
		read(fd, &((*pl)[i].number), sizeof(int));
		read(fd, type, sizeof(char) * 3);
		type[3] = '\0';
		if(strcmp(type, "HPL") == 0)
			(*pl)[i].type = HUMAN;
		else if(strcmp(type, "EST") == 0)
			(*pl)[i].type = BOT_EASIEST_MODE;
		else if(strcmp(type, "ESY") == 0)
			(*pl)[i].type = BOT_EASY;		
		else if(strcmp(type, "MED") == 0)
			(*pl)[i].type = BOT_MEDIUM;	
		else if(strcmp(type, "HRD") == 0)
			(*pl)[i].type = BOT_HARD;		
		read(fd, &((*pl)[i].r), sizeof(int));
		read(fd, &((*pl)[i].g), sizeof(int));
		read(fd, &((*pl)[i].b), sizeof(int));
		read(fd, &((*pl)[i].a), sizeof(int));
		read(fd, &connection, sizeof(int));
		(*pl)[i].next = &((*pl)[connection - 1]);
		lseek(fd, 1, SEEK_CUR);
	}
	for(i = 0; i < rows; i++)
		for(j = 0; j < columns; j++) {
			read(fd, &((*b)[i][j].balls), sizeof(int));
			read(fd, &((*b)[i][j].capacity), sizeof(int));
			read(fd, &s, sizeof(int));
			if(s == -1)
				(*b)[i][j].p = NULL;
			else 
				(*b)[i][j].p = &((*pl)[s - 1]);		
			lseek(fd, 1, SEEK_CUR);	
		}
	read(fd, &s, sizeof(int));
	*current = &((*pl)[s - 1]);	
	close(fd);
	return PLAYING;
}

void SaveGame(board b, player *pl, player *current, int players_number, int computer_players_number, char *filename) {
	int fd;
	int flag = FLAG_OFF;
	if(filename == NULL) {
		filename = (char *)malloc(sizeof(char) * 20);
		strcpy(filename, "savedgame1.chain");
		flag = FLAG_ON;
	}	
	fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR, S_IWUSR);
	if(flag == FLAG_ON)
		free(filename);	
	if(fd == -1) 
		return;	
	int i, j, nullbox = -1;
	write(fd, &rows, sizeof(int));
	write(fd, &columns, sizeof(int));
	write(fd, &players_number, sizeof(int));	
	write(fd, &computer_players_number, sizeof(int));
	write(fd, "\n", sizeof(char));
	for(i = 0; i < players_number + computer_players_number; i++)
		write(fd, &(ColorRow[i]), sizeof(SDL_Color));
	write(fd, "\n", sizeof(char));	
	for(i = 0; i < players_number + computer_players_number; i++) {
		write(fd, &(pl[i].number), sizeof(int));
		switch(pl[i].type) {
			case HUMAN:
				write(fd, "HPL", sizeof(char) * 3);
				break;
			case BOT_EASIEST_MODE:
				write(fd, "EST", sizeof(char) * 3);
				break;
			case BOT_EASY:
				write(fd, "ESY", sizeof(char) * 3);	
				break;
			case BOT_MEDIUM:
				write(fd, "MED", sizeof(char) * 3);	
				break;
			case BOT_HARD:
				write(fd, "HRD", sizeof(char) * 3);	
				break;
			default:
				break;	
		}
		write(fd, &(pl[i].r), sizeof(int));
		write(fd, &(pl[i].g), sizeof(int));
		write(fd, &(pl[i].b), sizeof(int));
		write(fd, &(pl[i].a), sizeof(int));
		write(fd, &(pl[i].next->number), sizeof(int));
		write(fd, "\n", sizeof(char));
	}
	for(i = 0; i < rows; i++)
		for(j = 0; j < columns; j++) {
			write(fd, &(b[i][j].balls), sizeof(int));
			write(fd, &(b[i][j].capacity), sizeof(int));
			if(b[i][j].p != NULL)
				write(fd, &(b[i][j].p->number), sizeof(int));
			else 
				write(fd, &nullbox, sizeof(int));	
			write(fd, "\n", sizeof(char));	
		}
	write(fd, &(current->number), sizeof(int));	
	write(fd, "\n", sizeof(char));	
	close(fd);	
}

void DestroyPlayer(player **pl_add) {
	free(*pl_add);
}

void DestroyBoard(board *b) {
	int i;
	for(i = 0; i < rows; i++)
		free((*b)[i]);
	free(*b);
}		


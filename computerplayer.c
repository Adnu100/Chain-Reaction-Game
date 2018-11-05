#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "chain.h"
#include <time.h>

extern int rows, columns;

int Random(int Range_Start, int Range_End) {
	srand((unsigned int)(time(NULL) + rand() + rand()));
	return (rand() % (1 + (Range_End > Range_Start ? Range_End : Range_Start) - (Range_Start < Range_End ? Range_Start : Range_End)) + (Range_Start < Range_End ? Range_Start : Range_End));
}	

void SetMove(board b, player *current, int *i, int *j) {
	*i = *j = 0;
	int x, y, impact, highest_impact = 0;
	int **impact_table = (int **)malloc(sizeof(int *) * rows);
	for(x = 0; x < rows; x++)
		impact_table[x] = (int *)malloc(sizeof(int) * columns);			
	int tolerate = 0;
	struct MOVE {
		int bx;
		int by;
	};
	struct MOVE *BEST_MOVE = (struct MOVE *)malloc(sizeof(struct MOVE) * rows * columns);	
	int count = 0;
	switch(current->type) {
		case HUMAN : 
			break;
		case BOT_EASIEST_MODE :
			do {
				*i = Random(0, rows - 1);
				*j = Random(0, columns - 1);
				if(b[*i][*j].p == NULL)
					break;
				else if(b[*i][*j].balls != b[*i][*j].capacity) {
					if(b[*i][*j].p->number == current->number)
						break;  		
					else 
						continue;
				}			
				else if(b[*i][*j].p->number == current->number) {
					if(tolerate > 15)
						break;
					else 
						tolerate++;	
				}		
			} while(FLAG_ON);
			break;
		case BOT_EASY : 
			do {
				*i = Random(0, rows -1);
				*j = Random(0, columns - 1);
			} while(b[*i][*j].p != NULL && b[*i][*j].p->number != current->number);
			break;
		case BOT_MEDIUM : 
			do {
				*i = Random(0, rows - 1);
				*j = Random(0, columns - 1);
				if(b[*i][*j].p == NULL) {
					if(tolerate > 30)
						break;
					else {
						tolerate++;
						continue;
					}	
				}	
				else if(b[*i][*j].balls == b[*i][*j].capacity) {
					if(b[*i][*j].p->number == current->number)
						break;  		
					else 
						continue;
				}			
				else if(b[*i][*j].p->number == current->number) {
					if(tolerate > 30)
						break;
					else 
						tolerate++;	
				}		
			} while(FLAG_ON);
			break;
		case BOT_HARD :
			for(x = 0; x < rows; x++) {
				for(y = 0; y < columns; y++) {
					impact = 0;
					if(b[x][y].p != NULL) {
						if(b[x][y].p->number != current->number) {
							impact = -100;
						}	
						else {
							if(b[x][y].balls == b[x][y].capacity) {
								if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number != current->number) {
									if(b[x - 1][y].balls == b[x - 1][y].capacity)
										impact += 10;
									else
										impact += 5;	
								}
								else if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number == current->number) {
									if((b[x - 1][y].balls == b[x - 1][y].capacity))
										impact -= 3;
									else
										impact += 1;		
								}
								if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number != current->number) {
									if(b[x + 1][y].balls == b[x + 1][y].capacity)
										impact += 10;
									else
										impact += 5;	
								}
								else if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number == current->number) {
									if((b[x + 1][y].balls == b[x + 1][y].capacity))
										impact -= 3;
									else
										impact += 1;		
								}
								if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number != current->number) {
									if(b[x][y - 1].balls == b[x][y - 1].capacity)
										impact += 10;
									else
										impact += 5;	
								}
								else if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number == current->number) {
									if((b[x][y - 1].balls == b[x][y - 1].capacity))
										impact -= 3;
									else
										impact += 1;		
								}
								if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number != current->number) {
									if(b[x][y + 1].balls == b[x][y + 1].capacity)
										impact += 10;
									else
										impact += 5;	
								}
								else if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number == current->number) {
									if((b[x][y + 1].balls == b[x][y + 1].capacity))
										impact -= 3;
									else
										impact += 1;		
								}
							}
							else if(b[x][y].balls == b[x][y].capacity - 1) {
								if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number != current->number) {
									if(b[x - 1][y].balls == b[x - 1][y].capacity)
										impact -= 10;
									else
										impact += 7;	
								}
								else if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number == current->number) {
									if((b[x - 1][y].balls == b[x - 1][y].capacity))
										impact -= 7;
									else
										impact += 1;		
								}
								if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number != current->number) {
									if(b[x + 1][y].balls == b[x + 1][y].capacity)
										impact -= 10;
									else
										impact += 7;	
								}
								else if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number == current->number) {
									if((b[x + 1][y].balls == b[x + 1][y].capacity))
										impact -= 7;
									else
										impact += 1;		
								}
								if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number != current->number) {
									if(b[x][y - 1].balls == b[x][y - 1].capacity)
										impact -= 10;
									else
										impact += 7;	
								}
								else if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number == current->number) {
									if((b[x][y - 1].balls == b[x][y - 1].capacity))
										impact -= 7;
									else
										impact += 1;		
								}
								if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number != current->number) {
									if(b[x][y + 1].balls == b[x][y + 1].capacity)
										impact -= 10;
									else
										impact += 7;	
								}
								else if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number == current->number) {
									if((b[x][y + 1].balls == b[x][y + 1].capacity))
										impact -= 7;
									else
										impact += 1;		
								}
							}
							else {
								if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number != current->number) {
									if(b[x - 1][y].balls == b[x - 1][y].capacity)
										impact -= 8;
									else if(b[x - 1][y].balls <= b[x][y].balls)
										impact += 10;
									else 
										impact -= 5;		
								}
								else if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number == current->number) {
									if((b[x - 1][y].balls == b[x - 1][y].capacity))
										impact += 0;
									else
										impact += 1;		
								}
								if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number != current->number) {
									if(b[x + 1][y].balls == b[x + 1][y].capacity)
										impact -= 8;
									else if(b[x + 1][y].balls <= b[x][y].balls)
										impact += 10;
									else 
										impact -= 5;	
								}
								else if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number == current->number) {
									if((b[x + 1][y].balls == b[x + 1][y].capacity))
										impact += 0;
									else
										impact += 1;		
								}
								if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number != current->number) {
									if(b[x][y - 1].balls == b[x][y - 1].capacity)
										impact -= 8;
									else if(b[x][y - 1].balls <= b[x][y].balls)
										impact += 10;
									else 
										impact -= 5;	
								}
								else if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number == current->number) {
									if((b[x][y - 1].balls == b[x][y - 1].capacity))
										impact += 0;
									else
										impact += 1;		
								}
								if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number != current->number) {
									if(b[x][y + 1].balls == b[x][y + 1].capacity)
										impact -= 8;
									else if(b[x][y + 1].balls <= b[x][y].balls)
										impact += 10;
									else 
										impact -= 5;	
								}
								else if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number == current->number) {
									if((b[x][y + 1].balls == b[x][y + 1].capacity))
										impact += 0;
									else
										impact += 1;		
								}
							}	
						}
					}
					else {
						if((x == 0 || x == rows - 1) && (y == 0 || y == columns - 1)) {
							impact += 11;
							if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number != current->number) {
								if(b[x - 1][y].balls == b[x - 1][y].capacity)
									impact -= 4;
								else
									impact += 3;		
							}
							else if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number == current->number) {
								if((b[x - 1][y].balls == b[x - 1][y].capacity))
									impact += 0;
								else
									impact += 2;		
							}
							if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number != current->number) {
								if(b[x + 1][y].balls == b[x + 1][y].capacity)
									impact -= 4;
								else 
									impact += 3;	
							}
							else if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number == current->number) {
								if((b[x + 1][y].balls == b[x + 1][y].capacity))
									impact += 0;
								else
									impact += 3;		
							}
							if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number != current->number) {
								if(b[x][y - 1].balls == b[x][y - 1].capacity)
									impact -= 4;
								else 
									impact += 3;	
							}
							else if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number == current->number) {
								if((b[x][y - 1].balls == b[x][y - 1].capacity))
									impact += 0;
								else
									impact += 3;		
							}
							if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number != current->number) {
								if(b[x][y + 1].balls == b[x][y + 1].capacity)
									impact -= 4;
								else 
									impact += 3;	
							}
							else if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number == current->number) {
								if((b[x][y + 1].balls == b[x][y + 1].capacity))
									impact += 0;
								else
									impact += 3;		
							}
						}
						else {
							if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number != current->number) {
								if(b[x - 1][y].balls == b[x - 1][y].capacity)
									impact -= 5;
								else
									impact -= 4;		
							}
							else if(x != 0 && b[x - 1][y].p != NULL &&  b[x - 1][y].p->number == current->number) {
								if((b[x - 1][y].balls == b[x - 1][y].capacity))
									impact += 3;
								else
									impact += 1;		
							}
							if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number != current->number) {
								if(b[x + 1][y].balls == b[x + 1][y].capacity)
									impact -= 5;
								else 
									impact -= 4;	
							}
							else if(x != rows - 1 && b[x + 1][y].p != NULL &&  b[x + 1][y].p->number == current->number) {
								if((b[x + 1][y].balls == b[x + 1][y].capacity))
									impact += 3;
								else
									impact += 1;		
							}
							if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number != current->number) {
								if(b[x][y - 1].balls == b[x][y - 1].capacity)
									impact -= 5;
								else 
									impact -= 4;	
							}
							else if(y != 0 && b[x][y - 1].p != NULL &&  b[x][y - 1].p->number == current->number) {
								if((b[x][y - 1].balls == b[x][y - 1].capacity))
									impact += 3;
								else
									impact += 1;		
							}
							if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number != current->number) {
								if(b[x][y + 1].balls == b[x][y + 1].capacity)
									impact -= 5;
								else 
									impact -= 4;	
							}
							else if(y != columns - 1 && b[x][y + 1].p != NULL &&  b[x][y + 1].p->number == current->number) {
								if((b[x][y + 1].balls == b[x][y + 1].capacity))
									impact += 3;
								else
									impact += 1;		
							}	
						}	
					}
					impact_table[x][y] = impact;
					if(impact > highest_impact)
						highest_impact = impact;	
				} 
			}
			for(x = 0; x < rows; x++)
				for(y = 0; y < columns; y++)
					if(impact_table[x][y] == highest_impact) {
						BEST_MOVE[count].bx = x;
						BEST_MOVE[count].by = y;
						count++;
					}
			count = Random(0, count - 1);
			if(BEST_MOVE[count].bx >= rows || BEST_MOVE[count].by >= columns)
				do {
					*i = Random(0, rows -1);
					*j = Random(0, columns - 1);
				} while(b[*i][*j].p != NULL && b[*i][*j].p->number != current->number);
			else {	
				*i = BEST_MOVE[count].bx;
				*j = BEST_MOVE[count].by;			
			}	
			break;
		case NIGHTMARE :
			break;				
	}	
	for(x = 0; x < rows; x++)
		free(*(impact_table + x));
	free(impact_table);
	free(BEST_MOVE);
}

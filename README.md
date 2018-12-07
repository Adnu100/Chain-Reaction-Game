# Chain Reaction Game
By - Adnesh Anil Dhamangaonkar

A chain reaction game which can be played by n human players or computer players. M * M board.
Game can be saved and resumed. Game is stored in a file.
The game can be played with humans as well as computer players. A game with all human or computer players is supported. Colors of players, computer player difficulty level, number of rows and columns can be set by users.

Game is written in pure C language and SDL2 (Simple DirectMedia Layer - A game engine). libraries used - stdio.h, stdlib.h, SDL.h, SDL_ttf.h, unistd.h, fcntl.h, types.h, stat.h (for file handling). The game uses a singly linked null terminated list data structure (called bucket). Also a Cell data structure which contains information of each cell on the board like balls in that cell, capacity of that cell, the pointer to the player which holds the possession of that cell (NULL if cell is empty). The player row data structure which is an array of structures containing each player information like its number, its type (whether human or computer), its color RGBA values and the pointer to the next player after it (although an array, used pointer because players can be knocked out in between game). The board is a pointer to the 2D array of the cells.

# Chain Reaction Game
###				By - Adnesh Anil Dhamangaonkar

A chain reaction game which can be played by n human players or computer players. M * M board.
Game can be saved and resumed. Game is stored in a file.
The game can be played with humans as well as computer players. A game with all human or computer players is supported. Colors of players, computer player difficulty level, number of rows and columns can be set by users.

Game is written in pure C language and SDL2 (Simple DirectMedia Layer - A game engine). libraries used - stdio.h, stdlib.h, SDL.h, SDL_ttf.h, unistd.h, fcntl.h, types.h, stat.h (for file handling). The game uses a singly linked null terminated list data structure (called bucket). Also a Cell data structure which contains information of each cell on the board like balls in that cell, capacity of that cell, the pointer to the player which holds the possession of that cell (NULL if cell is empty). The player row data structure which is an array of structures containing each player information like its number, its type (whether human or computer), its color RGBA values and the pointer to the next player after it (although an array, used pointer because players can be knocked out in between game). The board is a pointer to the 2D array of the cells.

## Getting Started
After cloning this project on your linux PC, go to folder and open in terminal. Just a few things to do before you can play this amazing game!

***The cell size can be varied depending on your PC resolution by changing macro `CELL_SIZE` in `src/headers/chain.h`***

### Prerequisites
This project required a C compiler (gcc prefered) and libraries like SDL2, SDL2_ttf installed on device. Make sure you have them.
simply running Install.sh would install all the required libraries. Run

`bash Install.sh`

Type password if asked for and press enter.

Or, to install individually if you already have some of them- first, to install gcc, type

```
sudo apt-get install gcc
```

Then to install SDL2 and SDL2_ttf

```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev
```

### Installing
To install the game, run make.sh 

`bash make.sh`

or simply

`./make.sh`

### Running

Finally, to start the game, run 

`chain`

or 

`./chain`

or, you can even launch the game by searching chain in the ubuntu search or double click the icon

You can know more about the command line options to be given by `-h` or `--help` 

`./chain -h`

`./chain --help`

### Uninstallation
To uninstall the game, run uninstall.sh script

`bash uninstall.sh`

or 

`./uninstall.sh`

you can install game again whenever needed by running make.sh script

## License
This project is licensed under GPL-3.0. See LICENSE for details.

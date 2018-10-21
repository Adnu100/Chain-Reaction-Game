game: chain.o backend_support.o visual_support.o computerplayer.o animation.o
	cc chain.o backend_support.o computerplayer.o animation.o visual_support.o -lSDL2 -lm -o game
computerplayer.o: computerplayer.c chain.h
	cc computerplayer.c -c -Wall				
chain.o: chain.c chain.h
	cc chain.c -c -Wall
backend_support.o: chain.h backend_support.c
	cc backend_support.c -c -Wall
animation.o: animation.c chain.h
	cc animation.c -c -Wall	
visual_support.o: visual_support.c chain.h
	cc visual_support.c -c -Wall	

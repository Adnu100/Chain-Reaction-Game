game: chain.o backend_support.o gameplay.o visual_support.o computerplayer.o animation.o bucket.o
	cc chain.o backend_support.o gameplay.o computerplayer.o animation.o visual_support.o bucket.o -lSDL2 -lSDL2_ttf -lm -o game
gameplay.o: gameplay.c chain.h bucket.h
	cc gameplay.c -c -Wall	
computerplayer.o: computerplayer.c chain.h bucket.h
	cc computerplayer.c -c -Wall				
chain.o: chain.c chain.h bucket.h
	cc chain.c -c -Wall
backend_support.o: chain.h backend_support.c bucket.h
	cc backend_support.c -c -Wall
animation.o: animation.c chain.h bucket.h
	cc animation.c -c -Wall	
visual_support.o: visual_support.c chain.h bucket.h
	cc visual_support.c -c -Wall	
bucket.o: bucket.c bucket.h
	cc bucket.c -c -Wall	

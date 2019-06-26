project: chain.o backend_support.o gameplay.o visual_support.o computerplayer.o animation.o bucket.o
	cc chain.o backend_support.o gameplay.o computerplayer.o animation.o visual_support.o bucket.o -lSDL2 -lSDL2_ttf -lm -o project
gameplay.o: gameplay.c headers/chain.h headers/bucket.h
	cc gameplay.c -c -Wall	
computerplayer.o: computerplayer.c headers/chain.h headers/bucket.h
	cc computerplayer.c -c -Wall				
chain.o: chain.c headers/chain.h headers/bucket.h
	cc chain.c -c -Wall
backend_support.o: headers/chain.h backend_support.c headers/bucket.h
	cc backend_support.c -c -Wall
animation.o: animation.c headers/chain.h headers/bucket.h
	cc animation.c -c -Wall	
visual_support.o: visual_support.c headers/chain.h headers/bucket.h
	cc visual_support.c -c -Wall	
bucket.o: bucket.c headers/bucket.h
	cc bucket.c -c -Wall	
clean:
	rm *.o *~ -f

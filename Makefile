CC = gcc
MAINCFLAGS = -lSDL2 -lSDL2_ttf -lm -O3
CFLAGS = -c -Wall -O3 -Wno-unused-result
INC = include
OBJ = obj
SRC = src
IFLAG = -I${INC}

all: objects chain

objects: ${OBJ}

${OBJ}:
	mkdir obj

chain: ${OBJ}/chain.o ${OBJ}/backend_support.o ${OBJ}/gameplay.o ${OBJ}/visual_support.o ${OBJ}/computerplayer.o ${OBJ}/animation.o ${OBJ}/bucket.o
	${CC} $^ ${MAINCFLAGS} -o $@

chain.h: bucket.h

${OBJ}/gameplay.o: ${SRC}/gameplay.c ${INC}/chain.h 
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

${OBJ}/computerplayer.o: ${SRC}/computerplayer.c ${INC}/chain.h 
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

${OBJ}/chain.o: ${SRC}/chain.c ${INC}/chain.h
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

${OBJ}/backend_support.o: ${SRC}/backend_support.c ${INC}/chain.h
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

${OBJ}/animation.o: ${SRC}/animation.c ${INC}/chain.h
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

${OBJ}/visual_support.o: ${SRC}/visual_support.c ${INC}/chain.h 
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

${OBJ}/bucket.o: ${SRC}/bucket.c ${INC}/bucket.h
	${CC} $< ${CFLAGS} ${IFLAG} -o $@

clean:
	rm ${SRC}/*~ ${INC}/*~ -f
	rm ${OBJ} -rf

CC=g++
CFLAGS=-c -Wall -std=c++11
SDL_CFLAGS=`sdl2-config --cflags`
SDL_LIBS=`sdl2-config --libs`
TTF_LIBS=-lSDL2_ttf

all: tetris

clean:
	rm *.o tetris

tetris: main.o GameLogic.o PlayField.o Tetri.o Renderer.o BlockAnimator.o
	$(CC) -std=c++11  main.o GameLogic.o PlayField.o Tetri.o Renderer.o BlockAnimator.o $(SDL_LIBS) $(TTF_LIBS)  -o tetris

main.o: main.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) main.cpp 

GameLogic.o: GameLogic.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) GameLogic.cpp

PlayField.o: PlayField.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) PlayField.cpp

Tetri.o: Tetri.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) Tetri.cpp

Renderer.o: Renderer.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) Renderer.cpp

BlockAnimator.o: BlockAnimator.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) BlockAnimator.cpp

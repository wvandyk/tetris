#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_ttf.h>

#include "PlayField.h"
#include "Tetri.h"
#include "GameLogic.h"
#include "Animator.h"
#include "BlockAnimator.h"
#include "Renderer.h"


int main(int argc, char **argv){
	std::srand(std::time(NULL));
	bool game_over = false;
	bool playing = false;
	Tetri *t = NULL;
	Renderer r;
	PlayField p;
	std::vector<Animator *> animators{};
	GameLogic l(animators);
	int lines_cleared = 0;

	std::cout << "Starting:" << std::endl;
	std::cout << "Animators size: " << animators.size() << std::endl;

	

	SDL_Event e;
	bool quit = false;
	t = NULL;

	while (quit == false) {

		if (!playing) {
			r.titleScreen();
		}

		if (playing) {
			if (t == NULL) {
				t = l.nextBlock();
			}
			
			if (game_over) {
				r.drawPlayfieldGrey(p);
				r.drawTopBorder();
				r.gameOverScreen();
				
				if (SDL_PollEvent(&e) == 1) {
					switch (e.type) {
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							playing = false;
							game_over = false;
							p.clearBoard();
							l.reset();
							break;
						}
					}
				}
			}
			else 
			{
				r.update(p, *t, l, animators);
				if (animators.size() > 0) {
					for (int i = 0; i < animators.size(); i++) {
						if (!(animators[i]->nextFrame())) {
							delete animators[i];
							animators.erase(animators.begin() + i);
						}
					}
				}


				l.GravityBlockDown(p, *t);

				if (t->getLocked()) {
					l.addBlock(p, *t);
					if (t->get_y() <= 1) {
						game_over = true;
						delete t;
						t = NULL;
						continue;
					}
					delete t;
					lines_cleared = l.clearLines(p);
					t = l.nextBlock();
				}


				if (SDL_PollEvent(&e) == 1) {
					switch (e.type) {
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_LEFT:
							l.moveBlockLeft(p, *t);
							l.kickFit(p, *t);
							break;
						case SDLK_RIGHT:
							l.moveBlockRight(p, *t);
							l.kickFit(p, *t);
							break;
						case SDLK_DOWN:
							l.moveBlockDown(p, *t);
							break;
						case SDLK_a:
							l.RotateBlockCCW(p, *t);
							l.kickFit(p, *t);
							break;
						case SDLK_d:
							l.RotateBlockCW(p, *t);
							l.kickFit(p, *t);
							break;
						case SDLK_f:
							std::cout << r.getFrameLenth() << std::endl;
							break;
						}
						break;
					}
				}
			}
		}
		else
		{
			if (SDL_PollEvent(&e) == 1) {
				switch (e.type) {
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_SPACE:
						playing = true;
						break;
					}
				}
			}
		}
	}
	
	delete t;
	return 0;
}

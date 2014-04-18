#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

#include "PlayField.h"
#include "Tetri.h"
#include "GameLogic.h"
#include "Animator.h"
#include "BlockAnimator.h"

class Renderer {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *tex;
	SDL_Texture *buf;

	std::string data_path;
	SDL_Rect irect, jrect, lrect, orect, srect, trect, zrect, grect, brect;
	std::vector<SDL_Rect *> blocks;
	Uint64 framelength = 0;

public:
	Uint64 getFrameLenth() {
		return framelength;
	}

	bool Sinitall() {
		char *base_path = SDL_GetBasePath();

		if (base_path) {
			data_path = SDL_strdup(base_path);
			SDL_free(base_path);
		}
		else {
			data_path = "./";
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}
		
		win = SDL_CreateWindow("Tetris", 400, 100, 800, 768,
			SDL_WINDOW_SHOWN);
		if (win == nullptr){
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return false;
		}

		ren = SDL_CreateRenderer(win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr){
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			return false;
		}
		
		SDL_Surface *bmp = SDL_LoadBMP((data_path + "/res/tetris.bmp").c_str());
		if (bmp == nullptr){
			std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
			return false;
		}

		tex = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		if (tex == nullptr){
			std::cout << "SDL_CreateTextureFromSurface Error: "
				<< SDL_GetError() << std::endl;
			return false;
		}

		buf = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 800, 768);
		if (tex == nullptr){
			std::cout << "SDL_CreateTexture error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	};

	Renderer(void) {
		blocks.reserve(8);
		blocks = { &irect, &jrect, &lrect, &orect, &srect, &trect, &zrect, &grect, &brect };
		for (int x = 0; x < 9; x++) {
			blocks[x]->x = 31 * x;
			blocks[x]->y = 0;
			blocks[x]->h = 31;
			blocks[x]->w = 31;
		}
		if (Sinitall()) {
			buildscr();
		};
	}

	void buildscr(void) {
		for (int y = 0; y < 24; y++) {
			for (int x = 0; x < 25; x++) {
				SDL_Rect t;
				t.x = x * 32;
				t.y = y * 32;
				t.w = 32;
				t.h = 32;
				SDL_RenderCopy(ren, tex, &grect, &t);
			}
		}

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 10; x++) {
				SDL_Rect t;
				t.x = x * 32 + 64;
				t.y = y * 32 + 64;
				t.w = 32;
				t.h = 32;
				SDL_RenderCopy(ren, tex, &brect, &t);
			}
		}

	}

	void drawplayfield(PlayField &p) {
		for (int y = 0; y < 22; y++) {
			for (int x = 0; x < 10; x++) {
				SDL_Rect t;
				t.x = x * 32 + 64;
				t.y = y * 32;
				t.w = 32;
				t.h = 32;
				int index = p.getBoardAt(x, y) - 1;
				if (index == -1) { index = 8; }
				SDL_RenderCopy(ren, tex, blocks[index], &t);
			}
		}
	}

	void drawtetri(Tetri &t) {
		if (&t == NULL) {
			return;
		}
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				SDL_Rect r;
				r.x = (t.get_x() + x) * 32 + 64;
				r.y = (t.get_y() + y) * 32;
				r.w = 32;
				r.h = 32;
				int index = t.getFrame()[x + y * 4] - 1;
				if (index >= 0) {
					SDL_RenderCopy(ren, tex, blocks[index], &r);
				}
			}
		}
	}

	void drawTopBorder() {
		for (int y = 0; y < 2; y++) {
			for (int x = 0; x < 25; x++) {
				SDL_Rect t;
				t.x = x * 32;
				t.y = y * 32;
				t.w = 32;
				t.h = 32;
				SDL_RenderCopy(ren, tex, &grect, &t);
			}
		}
	}

	void renderAnimator(std::vector<Animator *> &animators) {
		if (animators.size() > 0) {
			int i = 0;
			for (int i = 0; i < animators.size(); i++) {
				SDL_Rect t;
				t.x = ((BlockAnimator *)animators[i])->get_x();
				t.y = ((BlockAnimator *)animators[i])->get_y();
				t.w = ((BlockAnimator *)animators[i])->get_w();
				t.h = ((BlockAnimator *)animators[i])->get_h();
				int index = ((BlockAnimator *)animators[i])->get_block() - 1;
				if (index >= 0) {
					SDL_RenderCopy(ren, tex, blocks[index], &t);
				}
			}
		}
	}

	void update(PlayField &p, Tetri &t, std::vector<Animator *> &animators) {
		Uint64 tick = SDL_GetTicks();
		SDL_RenderClear(ren);
		buildscr();
		drawplayfield(p);
		drawtetri(t);
		drawTopBorder();
		renderAnimator(animators);
		SDL_RenderPresent(ren);

		framelength = SDL_GetTicks() - tick;
	}

	~Renderer(void) {
		SDL_DestroyTexture(tex);
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}

};

int main(int argc, char **argv){

	bool game_over = true;
	Tetri *t = NULL;
	Renderer r;
	PlayField p;
	std::vector<Animator *> animators{};
	GameLogic l(animators);
	int lines_cleared = 0;

	std::cout << "Starting:" << std::endl;
	std::cout << "Animators size: " << animators.size() << std::endl;

	
	t = l.nextBlock();
	SDL_Event e;
	bool quit = false;

	while (quit == false) {
		r.update(p, *t, animators);

		if (!game_over) {
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
					p.clearBoard();
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
						game_over = false;
						break;
					}
				}
			}
		}
	}
	
	delete t;
	return 0;
}
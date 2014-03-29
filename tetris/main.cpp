#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

#include "PlayField.h"
#include "Tetri.h"
#include "GameLogic.h"


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
		
		win = SDL_CreateWindow("Tetris", 100, 100, 800, 768,
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
		SDL_RenderClear(ren);
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
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 10; x++) {
				SDL_Rect t;
				t.x = x * 32 + 64;
				t.y = y * 32 + 64;
				t.w = 32;
				t.h = 32;
				int index = p.getBoardAt(x, y) - 1;
				if (index == -1) { index = 8; }
				SDL_RenderCopy(ren, tex, blocks[index], &t);
			}
		}
	}

	void drawtetri(Tetri &t) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				SDL_Rect r;
				r.x = (t.get_x() + x) * 32 + 64;
				r.y = (t.get_y() + y) * 32 + 64;
				r.w = 32;
				r.h = 32;
				int index = t.getFrame()[x + y * 4] - 1;
				if (index >= 0) {
					SDL_RenderCopy(ren, tex, blocks[index], &r);
				}
			}
		}
	}

	void update(PlayField &p, Tetri &t) {
		Uint64 tick = SDL_GetTicks();

		drawplayfield(p);
		drawtetri(t);
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


class Lblock : public Tetri {

public:
	Lblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			0, 3, 0, 0,
			0, 3, 0, 0,
			0, 3, 3, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 0, 0, 0,
			3, 3, 3, 0,
			3, 0, 0, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			3, 3, 0, 0,
			0, 3, 0, 0,
			0, 3, 0, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			0, 0, 3, 0,
			3, 3, 3, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		color = "orange";
	};
};

int main(int argc, char **argv){


	Lblock *t = new Lblock();
	Renderer r;
	PlayField p;
	GameLogic l;

	t->set_x(-1);
	if (l.checkFit(p, *t)) {
		std::cout << "block fits" << std::endl;
	}
	else 
	{
		std::cout << "doesnt fit" << std::endl;
	};

	t->set_x(15);
	t->set_y(20);

	if (l.checkFit(p, *t)) {
		std::cout << "block fits" << std::endl;
	}
	else
	{
		std::cout << "doesnt fit" << std::endl;
	};

	t->set_x(-1);
	t->set_y(5);

	if (l.checkFit(p, *t)) {
		std::cout << "block fits" << std::endl;
	}
	else
	{
		std::cout << "doesnt fit" << std::endl;
	};

	p.drawBoard();
	std::cout << "GOT HERE" << std::endl;
	t->set_x(14);
	if (l.adjustFit(p, *t)) {
		l.addBlock(p, *t);
	};
	std::cout << "GOT HERE2" << std::endl;
	p.drawBoard();

	if (l.checkFit(p, *t)) {
		std::cout << "block fits" << std::endl;
	}
	else
	{
		std::cout << "doesnt fit" << std::endl;
	};

	t->set_x(0);
	t->set_y(1);
	r.update(p, *t);
	std::cout << r.getFrameLenth() << std::endl;

	SDL_Delay(2000);

	t->set_y(2);
	r.update(p, *t);
	SDL_Delay(2000);

	std::cout << r.getFrameLenth() << std::endl;


	delete t;
	return 0;
}
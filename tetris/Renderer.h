#ifndef __RENDERER__
#define __RENDERER__

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Tetri.h"
#include "PlayField.h"
#include "Animator.h"
#include "GameLogic.h"

class Animator;
class GameLogic;

class Renderer {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *tex;
	SDL_Texture *buf;

	std::string data_path;
	SDL_Rect irect, jrect, lrect, orect, srect, trect, zrect, grect, brect;
	std::vector<SDL_Rect *> blocks;
	Uint64 framelength = 0;
	TTF_Font *font;
	SDL_Color orange, red, yellow, blue, violet, green, cyan, black, white;
	std::vector<int> title;

public:
	Renderer(void);
	Uint64 getFrameLenth(void);
	bool sdl_initall(void);
	void buildscr(void);
	void drawplayfield(PlayField &p);
	void drawtetri(Tetri &t);
	void drawRawTetri(Tetri &t, int x, int y);
	void drawTopBorder(void);
	void drawScoreArea(void);
	void drawScore(GameLogic &g);
	void drawLevel(GameLogic &g);
	void drawLines(GameLogic &g);
	void drawNextBlock(GameLogic &g);
	void renderBlock(int x, int y, int w, int h, int block);
	void renderAnimator(std::vector<Animator *> &animators);
	void update(PlayField &p, Tetri &t, GameLogic &g, std::vector<Animator *> &animators);
	void renderText(int x, int y, const char *text, SDL_Color &color);
	void titleScreen(void);
	void gameOverScreen(void);
	void drawPlayfieldGrey(PlayField &p);
	~Renderer(void);
};

#endif
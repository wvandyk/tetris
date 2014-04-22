#include "Renderer.h"
#include "BlockAnimator.h"

Uint64 Renderer::getFrameLenth() {
	return framelength;
}

bool Renderer::sdl_initall() {
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

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
		return false;
	}

	font = TTF_OpenFont((data_path + "/res/kremlin.ttf").c_str(), 32);
	if (!font) {
		std::cout << "TTF_OpenFontL " << TTF_GetError() << std::endl;
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

Renderer::Renderer(void) {
	title = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 2, 2, 2, 0, 3, 3, 3, 0, 4, 4, 4, 0, 5, 0, 6, 6, 6, 0, 0,
		0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 4, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 2, 2, 2, 0, 0, 3, 0, 0, 4, 4, 4, 0, 5, 0, 6, 6, 6, 0, 0,
		0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 4, 4, 0, 0, 5, 0, 0, 0, 6, 0, 0,
		0, 0, 0, 1, 0, 0, 2, 2, 2, 0, 0, 3, 0, 0, 4, 0, 4, 0, 5, 0, 6, 6, 6, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	blocks.reserve(8);
	blocks = { &irect, &jrect, &lrect, &orect, &srect, &trect, &zrect, &grect, &brect };
	for (int x = 0; x < 9; x++) {
		blocks[x]->x = 31 * x;
		blocks[x]->y = 0;
		blocks[x]->h = 31;
		blocks[x]->w = 31;
	}
	red = { 255, 0, 0 };
	orange = { 255, 128, 0 };
	yellow = { 255, 255, 0 };
	green = { 0, 255, 0 };
	blue = { 0, 0, 255 };
	violet = { 255, 0, 255 };
	cyan = { 0, 255, 255 };
	black = { 0, 0, 0 };
	white = { 255, 255, 255 };

	sdl_initall();
}

void Renderer::buildscr(void) {
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

void Renderer::drawplayfield(PlayField &p) {
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

void Renderer::drawPlayfieldGrey(PlayField &p) {
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 10; x++) {
			SDL_Rect t;
			t.x = x * 32 + 64;
			t.y = y * 32;
			t.w = 32;
			t.h = 32;
			int index = p.getBoardAt(x, y) - 1;
			
			if (index == -1) { 
				index = 8; 
			}
			else 
			{ 
				index = 7; 
			}
			SDL_RenderCopy(ren, tex, blocks[index], &t);
		}
	}
}

void Renderer::drawtetri(Tetri &t) {
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

void Renderer::drawRawTetri(Tetri &t, int x, int y) {

	if (&t == NULL) {
		return;
	}
	for (int yy = 0; yy < 4; yy++) {
		for (int xx = 0; xx < 4; xx++) {
			SDL_Rect r;
			r.x = (x + xx) * 32 + 64;
			r.y = (y + yy) * 32;
			r.w = 32;
			r.h = 32;
			int index = t.getFrame()[xx + yy * 4] - 1;

			if (index >= 0) {
				SDL_RenderCopy(ren, tex, blocks[index], &r);
			}
		}
	}
}

void Renderer::drawTopBorder() {
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

void Renderer::renderAnimator(std::vector<Animator *> &animators) {
	if (animators.size() > 0) {
		int i = 0;
		for (int i = 0; i < animators.size(); i++) {
			animators[i]->render(*this);
		}
	}
}

void Renderer::update(PlayField &p, Tetri &t, GameLogic &g, std::vector<Animator *> &animators) {
	Uint64 tick = SDL_GetTicks();
	SDL_RenderClear(ren);
	buildscr();
	drawplayfield(p);
	drawScoreArea();
	drawNextBlock(g);
	drawScore(g);
	drawLevel(g);
	drawLines(g);
	drawtetri(t);
	drawTopBorder();
	renderAnimator(animators);

	SDL_RenderPresent(ren);

	framelength = SDL_GetTicks() - tick;
}

void Renderer::renderText(int x, int y, const char *text, SDL_Color &color) {
	SDL_Rect text_rect;
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;

	text_rect.x = x;
	text_rect.y = y;

	if (TTF_SizeText(font, text, &text_rect.w, &text_rect.h) != 0) {
		std::cout << "Error! : " << TTF_GetError() << std::endl;
	}

	if (!(text_surface = TTF_RenderText_Blended(font, text, color))) {
		std::cout << "Error! : " << TTF_GetError() << std::endl;
	}
	else
	{
		text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
		if (!text_texture) {
			std::cout << "ERROR! " << SDL_GetError();
		}
		SDL_FreeSurface(text_surface);
		SDL_RenderCopy(ren, text_texture, NULL, &text_rect);
		SDL_DestroyTexture(text_texture);
	}
}

void Renderer::renderBlock(int x, int y, int w, int h, int block) {
	SDL_Rect t;
	t.x = x;
	t.y = y;
	t.w = w;
	t.h = h;
	if (block >= 0) {
		SDL_RenderCopy(ren, tex, blocks[block], &t);
	}
}

void Renderer::drawScoreArea(void) {
	for (int y = 2; y < 22; y++) {
		for (int x = 14; x < 23; x++) {
			SDL_Rect t;
			t.x = x * 32;
			t.y = y * 32;
			t.w = 32;
			t.h = 32;
			SDL_RenderCopy(ren, tex, &brect, &t);
		}
	}
}

void padTo(std::string &str, const size_t num, const char paddingChar = ' ')
{
	if (num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}

void Renderer::drawScore(GameLogic &g) {
	std::string scoreString;

	scoreString = std::to_string(g.getScore());
	padTo(scoreString, 12, '0');
	int x = 14 * 32 + 2;
	int y = 7 * 32;
	renderText(x, y, "SCOrE:", white);
	y = 8 * 32;
	renderText(x, y, scoreString.c_str(), white);
}

void Renderer::drawLevel(GameLogic &g) {
	std::string levelString;

	levelString = std::to_string(g.getLevel());
	padTo(levelString, 2, '0');
	int x = 14 * 32 + 2;
	int y = 10 * 32;
	renderText(x, y, "LEVEL:", white);
	y = 11 * 32;
	renderText(x, y, levelString.c_str(), white);
}

void Renderer::drawLines(GameLogic &g) {
	std::string linesString;

	linesString = std::to_string(g.getLines());
	padTo(linesString, 4, '0');
	int x = 14 * 32 + 2;
	int y = 13 * 32;
	renderText(x, y, "LINES:", white);
	y = 14 * 32;
	renderText(x, y, linesString.c_str(), white);
}

void Renderer::drawNextBlock(GameLogic &g) {
	int x = 14 * 32 + 2;
	int y = 2 * 32;
	Tetri *piece = g.getNextPiece();
	renderText(x, y, "NEXT:", white);
	y = 3 * 32;
	drawRawTetri(*piece, 10 + piece->get_x(), 4 + piece->get_y());
}

void Renderer::titleScreen() {
	int block;

	
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	for (int y = 0; y < 24; y++) {
		for (int x = 0; x < 25; x++) {
			SDL_Rect t;
			t.x = x * 32;
			t.y = y * 32;
			t.w = 31;
			t.h = 31;
			block = title[x + y * 25];
			if (block > 0) {
				SDL_RenderCopy(ren, tex, blocks[block], &t);
			}
		}
	}

	renderText(7 * 32, 11 * 32, "BY WYNAND VAN DYK", green);
	renderText(6 * 32, 13 * 32, "PrESS SPACE TO PLAY", white);
	renderText(6 * 32, 15 * 32, "PrESS ESCAPE TO QUIT", white);
	SDL_RenderPresent(ren);
}

void Renderer::gameOverScreen() {
	renderText(4 * 32, 5 * 32, "GAME OVER!", red);
	renderText(3 * 32, 7 * 32, "PrESS ESCAPE", blue);
	SDL_RenderPresent(ren);
}

Renderer::~Renderer(void) {
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_CloseFont(font);
	font = NULL;
	TTF_Quit();
	SDL_Quit();
}

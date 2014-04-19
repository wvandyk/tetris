#ifndef __BLOCK_ANIMATOR__
#define __BLOCK_ANIMATOR__
#include "Animator.h"
#include <SDL.h>

class BlockAnimator : public Animator {
	int z = 256;
	int centerx = 4 * 32 + 64;
	int centery = 0;
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;
	int block = 0;
	Uint64 ticktime = 10;
	Uint64 last_tick = SDL_GetTicks();

public:
	BlockAnimator(int x, int y, int x2, int y2, int block);
	bool nextFrame(void);
	int get_x(void);
	int get_y(void);
	int get_w(void);
	int get_h(void);
	int get_block(void);
	~BlockAnimator();
};

#endif
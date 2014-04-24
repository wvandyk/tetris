#ifndef TETRIS_BLOCK_ANIMATOR_H_
#define TETRIS_BLOCK_ANIMATOR_H_

#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include "Animator.h"


class BlockAnimator : public Animator {
	int z;
	int centerx;
	int centery;
	int x;
	int y;
	int x2;
	int y2;
	int block;
	Uint64 ticktime;
	Uint64 last_tick;

public:
	BlockAnimator(int x, int y, int x2, int y2, int block);
	bool nextFrame(void);
	void render(Renderer &r);
	~BlockAnimator();
};

#endif // TETRIS_BLOCK_ANIMATOR_H_

#include "BlockAnimator.h"
#include "Renderer.h"
#include <iostream>

BlockAnimator::BlockAnimator(int x, int y, int x2, int y2, int block) {
	centery = ((y / 32) - 2) * 32;
	this->x = x - centerx;
	this->y = y - centery;
	this->x2 = x2 - centerx;
	this->y2 = y2 - centery;
	this->block = block;
};

bool BlockAnimator::nextFrame(void) {
	Uint64 tick = SDL_GetTicks();
	if (tick - last_tick >= ticktime) {
		last_tick = tick;
		if ((this->x + centerx <= 0) && (this->x2 + centerx <= 0) ||
			(this->x + centerx >= 800) && (this->x2 + centerx >= 800) ||
			(this->y + centery <= 0) && (this->y2 + centery <= 0) ||
			(this->y + centery >= 768) && (this->y2 + centery >= 768) || z <= 100) {
			return false;
		}
		else
		{
			this->x = this->x * 256 / z;
			this->y = this->y * 256 / z;
			this->x2 = this->x2 * 256 / z;
			this->y2 = this->y2 * 256 / z;
			z = z - 2;
		}
		return true;
	}
	return true;
};

void BlockAnimator::render(Renderer &r) {
	r.renderBlock(x + centerx, y + centery, x2 - x, y2 - y, block - 1);
}

BlockAnimator::~BlockAnimator() {
}

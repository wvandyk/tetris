#include "BlockAnimator.h"
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
	if (SDL_GetTicks() - last_tick >= ticktime) {
		last_tick = SDL_GetTicks();
		if ((this->x + centerx <= 0) && (this->x2 + centerx <= 0) ||
			(this->x + centerx >= 800) && (this->x2 + centerx >= 800) ||
			(this->y + centery <= 0) && (this->y2 + centery <= 0) ||
			(this->y + centery >= 768) && (this->y2 + centery >= 768) || z <= 100) {
			std::cout << "Returning false" << std::endl;
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

BlockAnimator::~BlockAnimator() {
}

int BlockAnimator::get_x(void) {
	return x + centerx;
};

int BlockAnimator::get_y(void) {
	return y + centery;
};

int BlockAnimator::get_w(void) {
	return x2 - x;
};

int BlockAnimator::get_h(void) {
	return y2 - y;
};

int BlockAnimator::get_block(void) {
	return block;
};

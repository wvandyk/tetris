#include "BlockAnimator.h"

BlockAnimator::BlockAnimator(int _x, int _y, int _x2, int _y2, int _block)
: z(256),
  centerx(4 * 32 + 64),
  centery((_y / 32 - 2) * 32),
  x(_x - centerx),
  y(_y - centery),
  x2(_x2 - centerx),
  y2(_y2 - centery),
  block(_block),
  ticktime(10),
  last_tick(SDL_GetTicks()) {}

bool BlockAnimator::nextFrame(void) {
	Uint64 tick = SDL_GetTicks();
	if (tick - last_tick >= ticktime) {
		last_tick = tick;
		if ((x + centerx <= 0) && (x2 + centerx <= 0) ||
			(x + centerx >= 800) && (x2 + centerx >= 800) ||
			(y + centery <= 0) && (y2 + centery <= 0) ||
			(y + centery >= 768) && (y2 + centery >= 768) || z <= 100) {
			return false;
		} else {
			x = x * 256 / z;
			y = y * 256 / z;
			x2 = x2 * 256 / z;
			y2 = y2 * 256 / z;
			z = z - 2;
		}
	}
	return true;
};

void BlockAnimator::render(Renderer &r) {
	r.renderBlock(x + centerx, y + centery, x2 - x, y2 - y, block - 1);
}

BlockAnimator::~BlockAnimator() {}

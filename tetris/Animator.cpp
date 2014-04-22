#include "Animator.h"

Animator::Animator() {};

bool Animator::nextFrame(void) {
	if (frame == frame_count) {
		return false;
	}
	frame++;
	return true;
};

void Animator::render(Renderer &r) {
	return;
}
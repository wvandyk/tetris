#ifndef TETRIS_ANIMATOR_H_
#define TETRIS_ANIMATOR_H_

#include "Renderer.h"

class Renderer;

class Animator {
public:
	virtual bool nextFrame() = 0;
	virtual void render(Renderer &r) = 0;
	virtual ~Animator() {}
};

#endif // TETRIS_ANIMATOR_H_

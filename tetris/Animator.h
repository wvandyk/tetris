#ifndef __ANIMATOR__
#define __ANIMATOR__

#include "Renderer.h"

class Renderer;

class Animator {
	int frame = 0;
	int frame_count = 10;
public:
	Animator();
	virtual bool nextFrame(void);
	virtual void render(Renderer &r);
	virtual ~Animator() {};
};

#endif
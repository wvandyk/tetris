#ifndef __TEXTANIMATOR__
#define __TEXTANIMATOR__

#include "Animator.h"

class TextAnimator : public Animator {
public:
	TextAnimator(char *text);
	void nextFrame();
	void render();
};

#endif
#ifndef __ANIMATOR__
#define __ANIMATOR__

class Animator {
	int frame = 0;
	int frame_count = 10;
public:
	Animator();
	bool nextFrame(void);
};

#endif
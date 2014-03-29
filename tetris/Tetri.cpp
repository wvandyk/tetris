#include "Tetri.h"

int Tetri::incFrame(void) {
	curFrame = (curFrame + 1) % 4;
	return curFrame;
};

int Tetri::decFrame(void) {
	curFrame = (curFrame - 1);
	if (curFrame < 0) { curFrame = 3; }
	return curFrame;
}

void Tetri::rotateCW(void) {
	incFrame();
}

void Tetri::rotateCCW(void) {
	decFrame();
}

int *Tetri::getFrame(void) {
	return &frames[curFrame][0];
};

std::string Tetri::getColor(void) {
	return color;
};

int Tetri::get_x(void) {
	return x;
};

int Tetri::get_y(void) {
	return y;
};

void Tetri::set_x(int new_x) {
	x = new_x;
};

void Tetri::set_y(int new_y) {
	y = new_y;
};

int Tetri::xOfLeftMostBlock(void) {
	int least_x = 10;
	for (int ty = 0; ty < 4; ty++) {
		for (int tx = 0; tx < 4; tx++) {
			if (((this->getFrame())[tx + ty * 4] != 0) && (tx < least_x)) {
				least_x = tx;
			}
		}
	}
	return least_x;
}

int Tetri::xOfRightMostBlock(void) {
	int most_x = -10;
	for (int ty = 0; ty < 4; ty++) {
		for (int tx = 0; tx < 4; tx++) {
			if (((this->getFrame())[tx + ty * 4] != 0) && (tx > most_x)) {
				most_x = tx;
			}
		}
	}
	return most_x;
};
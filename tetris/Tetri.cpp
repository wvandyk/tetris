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

void Tetri::setLockTimer(Uint64 time) {
	lockTimer = time;
};

Uint64 Tetri::getLockTimer(void) {
	return lockTimer;
};

void Tetri::setLocked(bool val) {
	locked = val;
}

bool Tetri::getLocked(void) {
	return locked;
}


	Lblock::Lblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			0, 0, 3, 0,
			3, 3, 3, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 3, 0, 0,
			0, 3, 0, 0,
			0, 3, 3, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 0, 0, 0,
			3, 3, 3, 0,
			3, 0, 0, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			3, 3, 0, 0,
			0, 3, 0, 0,
			0, 3, 0, 0,
			0, 0, 0, 0 };
		color = "orange";
		x = 3;
		y = 0;
	};

	Iblock::Iblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0 };

		color = "cyan";
		x = 3;
		y = -1;
	};

	Jblock::Jblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			2, 0, 0, 0,
			2, 2, 2, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 2, 2, 0,
			0, 2, 0, 0,
			0, 2, 0, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 0, 0, 0,
			2, 2, 2, 0,
			0, 0, 2, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			0, 2, 0, 0,
			0, 2, 0, 0,
			2, 2, 0, 0,
			0, 0, 0, 0 };

		color = "blue";
		x = 3;
		y = 0;
	};

	Oblock::Oblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			0, 4, 4, 0,
			0, 4, 4, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 4, 4, 0,
			0, 4, 4, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 4, 4, 0,
			0, 4, 4, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			0, 4, 4, 0,
			0, 4, 4, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		color = "yellow";
		x = 3;
		y = 0;
	};

	Sblock::Sblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			0, 5, 5, 0,
			5, 5, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 5, 0, 0,
			0, 5, 5, 0,
			0, 0, 5, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 0, 0, 0,
			0, 5, 5, 0,
			5, 5, 0, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			5, 0, 0, 0,
			5, 5, 0, 0,
			0, 5, 0, 0,
			0, 0, 0, 0 };
		color = "green";
		x = 3;
		y = 0;
	};

	Tblock::Tblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			0, 6, 0, 0,
			6, 6, 6, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 6, 0, 0,
			0, 6, 6, 0,
			0, 6, 0, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 0, 0, 0,
			6, 6, 6, 0,
			0, 6, 0, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			0, 6, 0, 0,
			6, 6, 0, 0,
			0, 6, 0, 0,
			0, 0, 0, 0 };
		color = "violet";
		x = 3;
		y = 0;
	};

	Zblock::Zblock() {
		frames.resize(4);
		frames[0].resize(16);
		frames[0] = {
			7, 7, 0, 0,
			0, 7, 7, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
		frames[1].resize(16);
		frames[1] = {
			0, 0, 7, 0,
			0, 7, 7, 0,
			0, 7, 0, 0,
			0, 0, 0, 0 };
		frames[2].resize(16);
		frames[2] = {
			0, 0, 0, 0,
			7, 7, 0, 0,
			0, 7, 7, 0,
			0, 0, 0, 0 };
		frames[3].resize(16);
		frames[3] = {
			0, 7, 0, 0,
			7, 7, 0, 0,
			7, 0, 0, 0,
			0, 0, 0, 0 };
		color = "red";
		x = 3;
		y = 0;
	};

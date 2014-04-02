#ifndef __TETRI__
#define __TETRI__
#include <SDL.h>
#include <string>
#include <vector>

class Tetri {
protected:
	int x = 0;
	int y = 0;
	int curFrame = 0;
	bool locked;
	Uint64 lockTimer = 0;
	std::vector< std::vector<int> > frames;
	std::string color = "green";

public:
	void setLockTimer(Uint64 time);
	Uint64 getLockTimer(void);
	void setLocked(bool val);
	bool getLocked(void);
	int incFrame(void);
	int decFrame(void);
	int *getFrame(void);
	std::string getColor(void);
	int get_x(void);
	int get_y(void);
	void set_x(int);
	void set_y(int);
	void rotateCW(void);
	void rotateCCW(void);
	int xOfLeftMostBlock(void);
	int xOfRightMostBlock(void);
	virtual ~Tetri() {};
};

class Lblock : public Tetri {
public:
	Lblock();
};

class Iblock : public Tetri {
public:
	Iblock();
};

class Jblock : public Tetri {
public:
	Jblock();
};

class Oblock : public Tetri {
public:
	Oblock();
};

class Sblock : public Tetri {
public:
	Sblock();
};

class Tblock : public Tetri {
public:
	Tblock();
};

class Zblock : public Tetri {
public:
	Zblock();
};

#endif
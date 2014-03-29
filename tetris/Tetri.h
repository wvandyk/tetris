#ifndef __TETRI__
#define __TETRI__
#include <string>
#include <vector>

class Tetri {
protected:
	int x = 0;
	int y = 0;
	int curFrame = 0;
	std::vector< std::vector<int> > frames;
	std::string color = "green";

public:
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

#endif
#ifndef __PLAYFIELD__
#define __PLAYFIELD__
#include <iostream>
#include <vector>

class PlayField {
private:
	std::vector<int> board;

public:

	PlayField();
	bool setBoardAt(int x, int y, int val);
	int getBoardAt(int x, int y);
	bool checkInBounds(int x, int y);
	bool boardEmptyAt(int x, int y);
	void drawBoard(void);
	void clearBoard(void);
};

#endif
#ifndef TETRIS_PLAYFIELD_H_
#define TETRIS_PLAYFIELD_H_
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
	void drawBoard();
	void clearBoard();
};

#endif // TETRIS_PLAYFIELD_H_

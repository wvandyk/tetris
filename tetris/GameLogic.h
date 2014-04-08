#ifndef __GAMELOGIC__
#define __GAMELOGIC__
#include "PlayField.h"
#include "Tetri.h"

class GameLogic {
private:
	Uint64 lockTimeOut = 1600;
	Uint64 dropTimeout = 800;
	Uint64 lastDrop = 0;
	std::vector<int> blockbag;
public:
	GameLogic();
	bool adjustFit(PlayField &board, Tetri &block);
	bool kickFit(PlayField &board, Tetri &block);
	bool checkFit(PlayField &p, Tetri &block);
	bool addBlock(PlayField &p, Tetri &block);
	void moveBlockLeft(PlayField &p, Tetri &block);
	void moveBlockRight(PlayField &p, Tetri &block);
	void moveBlockDown(PlayField &p, Tetri &block);
	void RotateBlockCW(PlayField &p, Tetri &block);
	void RotateBlockCCW(PlayField &p, Tetri &block);
	void GravityBlockDown(PlayField &p, Tetri &block);
	Tetri *nextBlock(void);
	void clearLines(PlayField &p);
};

#endif
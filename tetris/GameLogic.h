#ifndef __GAMELOGIC__
#define __GAMELOGIC__
#include "PlayField.h"
#include "Tetri.h"

class GameLogic {
public:
	bool adjustFit(PlayField &board, Tetri &block);
	bool checkFit(PlayField &p, Tetri &block);
	bool addBlock(PlayField &p, Tetri &block);
	void moveBlockLeft(PlayField &p, Tetri &block);
	void moveBlockRight(PlayField &p, Tetri &block);
	void moveBlockDown(PlayField &p, Tetri &block);
	void RotateBlockCW(PlayField &p, Tetri &block);
	void RotateBlockCCW(PlayField &p, Tetri &block);
};

#endif
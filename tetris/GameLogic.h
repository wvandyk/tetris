#ifndef __GAMELOGIC__
#define __GAMELOGIC__
#include "PlayField.h"
#include "Tetri.h"

class GameLogic {
public:
	bool adjustFit(PlayField &board, Tetri &block);
	bool checkFit(PlayField &p, Tetri &block);
	bool addBlock(PlayField &p, Tetri &block);
};

#endif
#ifndef __GAMELOGIC__
#define __GAMELOGIC__
#include "PlayField.h"
#include "Tetri.h"
#include "Animator.h"

class Animator;

class GameLogic {
private:
	Uint64 lockTimeOut = 1600;
	Uint64 dropTimeout = 800;
	Uint64 lastDrop = 0;
	Uint64 score = 0;
	Uint64 lines_completed = 0;
	int lines_to_level = 10;
	Uint64 level = 0;
	std::vector<int> blockbag;
	std::vector<Animator *> *alist;
	Tetri *nnextPiece = NULL;
	Tetri *nextPiece = NULL;
public:
	GameLogic(std::vector<Animator *> &animlist);
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
	Uint64 getScore(void);
	Uint64 getLevel(void);
	Uint64 getLines(void);
	Tetri *nextBlock(void);
	Tetri *drawPiece(void);
	Tetri *getNextPiece(void);
	int clearLines(PlayField &p);
	void reset(void);
	~GameLogic(void);
};

#endif
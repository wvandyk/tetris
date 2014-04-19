#include "GameLogic.h"
#include "Animator.h"
#include "BlockAnimator.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

GameLogic::GameLogic(std::vector<Animator *> &animlist) {
	lockTimeOut = 800;
	dropTimeout = 400;
	lastDrop = 0;
	blockbag.reserve(7);
	blockbag = { 1, 2, 3, 4, 5, 6, 7 };
	std::srand(std::time(NULL));
	alist = &animlist;
}

int GameLogic::clearLines(PlayField &p) {
	int lcount = 0;
	int cleared = 0;

	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 10; x++) {
			if (p.getBoardAt(x, y) != 0) {
				lcount++;
			}
		}
		if (lcount == 10) {
			cleared++;
			for (int x = 0; x < 10; x++) {
				alist->push_back(new BlockAnimator(x * 32 + 64, y * 32, x * 32 + 64 + 31, y * 32 + 31, p.getBoardAt(x, y)));
				p.setBoardAt(x, y, 0);
			}
			for (int yy = y; yy > 0; yy--) {
				for (int xx = 0; xx < 10; xx++) {
					int tv = p.getBoardAt(xx, yy - 1);
					p.setBoardAt(xx, yy, tv);
				}
			}
		}
		lcount = 0;
	}
	if (cleared > 0) {
		lines_completed = lines_completed + cleared;
		score = score + cleared * 100 * cleared * cleared;
		lines_to_level = lines_to_level - cleared;
		if (lines_to_level <= 0) {
			level++;
			lines_to_level = 10 + (level * 5);
			dropTimeout = dropTimeout - 20;
		}
		std::cout << "Score: " << score << std::endl;
		std::cout << "Level: " << level << std::endl;
		std::cout << "Lines: " << lines_completed << std::endl;
		std::cout << "Lines to Level: " << lines_to_level << std::endl;
		std::cout << "droptimeout: " << dropTimeout << std::endl;
	}
	switch (cleared) {
	case 1:
		std::cout << "Single!" << std::endl;
		break;
	case 2:
		std::cout << "Double!" << std::endl;
		break;
	case 3:
		std::cout << "Triple!" << std::endl;
		break;
	case 4:
		std::cout << "TETRIS!" << std::endl;
		break;
	}
	return cleared;
}

Tetri *GameLogic::nextBlock(void) {
	Tetri *nextpiece;
	int r = std::rand() % blockbag.size();
	int piece = blockbag[r];
	blockbag.erase(blockbag.begin() + r);
	
	if (blockbag.size() == 0) {
		blockbag = { 1, 2, 3, 4, 5, 6, 7 };
	}

	switch (piece) {
	case 1:
		nextpiece = new Iblock();
		break;
	case 2:
		nextpiece = new Lblock();
		break;
	case 3:
		nextpiece = new Jblock();
		break;
	case 4:
		nextpiece = new Oblock();
		break;
	case 5:
		nextpiece = new Sblock();
		break;
	case 6:
		nextpiece = new Tblock();
		break;
	case 7:
		nextpiece = new Zblock();
		break;
	default:
		nextpiece = NULL;
		break;
	}

	return nextpiece;
}

bool GameLogic::adjustFit(PlayField &board, Tetri &block) {
	int original_x = block.get_x();
	int original_y = block.get_y();
	if (checkFit(board, block)) {
		return true;
	}
	else {
		while (((block.xOfLeftMostBlock() + block.get_x()) < 0) && (checkFit(board, block) == false)) {
			block.set_x(block.get_x() + 1);
		}
		while (((block.xOfRightMostBlock() + block.get_x()) > 9) && (checkFit(board, block) == false)) {
			block.set_x(block.get_x() - 1);
		}
	}
	if (!checkFit(board, block)) {
		block.set_y(original_y);
		block.set_x(original_x);
		return false;
	}
	return true;
};

bool GameLogic::kickFit(PlayField &board, Tetri &block) {
	int original_x = block.get_x();
	int original_y = block.get_y();

	if (!checkFit(board, block)) {
		block.set_y(original_y);
		block.set_x(original_x + 1);
		if (!checkFit(board, block)) {
			block.set_x(original_x - 1);
			if (!checkFit(board, block)) {
				block.set_x(original_x);
				return false;
			}
			return true;
		}
		block.set_x(original_x);
	}
	return false;
}

bool GameLogic::checkFit(PlayField &p, Tetri &block) {
	int *frame = block.getFrame();
	int pos_x = block.get_x();
	int pos_y = block.get_y();

	for (int i_y = 0; i_y < 4; i_y++) {
		for (int i_x = 0; i_x < 4; i_x++) {
			if (frame[i_x + i_y * 4] != 0) {
				if (!((p.checkInBounds(i_x + pos_x, i_y + pos_y)) && p.boardEmptyAt(i_x + pos_x, i_y + pos_y))) {
					return false;
				}
			}
		}
	}
	return true;
};

bool GameLogic::addBlock(PlayField &p, Tetri &block) {
	int *frame = block.getFrame();
	int pos_x = block.get_x();
	int pos_y = block.get_y();

	for (int i_y = 0; i_y < 4; i_y++) {
		for (int i_x = 0; i_x < 4; i_x++) {
			if (frame[i_x + i_y * 4] != 0) {
				if ((p.checkInBounds(i_x + pos_x, i_y + pos_y)) && p.boardEmptyAt(i_x + pos_x, i_y + pos_y)) {
					p.setBoardAt(i_x + pos_x, i_y + pos_y, frame[i_x + i_y * 4]);
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
};

void GameLogic::moveBlockLeft(PlayField &p, Tetri &block) {
	int t_x = block.get_x();
	int t_y = block.get_y();

	block.set_x(t_x - 1);
	if (!adjustFit(p, block)) {
		block.set_x(t_x);
		block.set_y(t_y);
	}
};

void GameLogic::moveBlockRight(PlayField &p, Tetri &block) {
	int t_x = block.get_x();
	int t_y = block.get_y();

	block.set_x(t_x + 1);
	if (!adjustFit(p, block)) {
		block.set_x(t_x);
		block.set_y(t_y);
	}
};

void GameLogic::moveBlockDown(PlayField &p, Tetri &block) {
	int t_x = block.get_x();
	int t_y = block.get_y();

	block.set_y(t_y + 1);
	if (!adjustFit(p, block)) {
		block.set_x(t_x);
		block.set_y(t_y);
	}
};

void GameLogic::RotateBlockCW(PlayField &p, Tetri &block) {
	int t_x = block.get_x();
	int t_y = block.get_y();

	block.rotateCW();
	if (!adjustFit(p, block)) {
		block.rotateCCW();
		block.set_x(t_x);
		block.set_y(t_y);
	}
};

void GameLogic::RotateBlockCCW(PlayField &p, Tetri &block) {
	int t_x = block.get_x();
	int t_y = block.get_y();

	block.rotateCCW();
	if (!adjustFit(p, block)) {
		block.rotateCW();
		block.set_x(t_x);
		block.set_y(t_y);
	}
};

void GameLogic::GravityBlockDown(PlayField &p, Tetri &block) {
	int t_x = block.get_x();
	int t_y = block.get_y();

	if (SDL_GetTicks() - lastDrop >= dropTimeout) {
		block.set_y(t_y + 1);
		lastDrop = SDL_GetTicks();

		if (!adjustFit(p, block)) {
			block.set_y(t_y);
			block.set_x(t_x);
			if (block.getLockTimer() == 0) {
				block.setLockTimer(SDL_GetTicks());
			}
			else 
			{
				if (SDL_GetTicks() - block.getLockTimer() >= lockTimeOut) {
					block.setLocked(true);
				}
			}
		}
		else 
		{
			block.setLockTimer(0);
		}
	}
}
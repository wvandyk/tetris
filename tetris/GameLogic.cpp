#include "GameLogic.h"

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
		block.set_x(original_x);
		block.set_y(original_y);
		return false;
	};
	return true;
};

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

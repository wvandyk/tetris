#include "PlayField.h"

bool PlayField::checkInBounds(int x, int y) {
	if ((x >= 0) && (x < 10) && (y >= 0) && (y < 22)) {
		return true;
	}
	return false;
}

bool PlayField::boardEmptyAt(int x, int y) {
	if (board[x + y * 10] == 0) {
		return true;
	}
	return false;
}

PlayField::PlayField() 
  : board(220, 0) {}

bool PlayField::setBoardAt(int x, int y, int val) {
	int index = x + y * 10;
	if (index < 220 && index > 0) {
		board[index] = val;
		return true;
	}
	return false;
}

int PlayField::getBoardAt(int x, int y) {
	int index = x + y * 10;
	if (index < 220 && index >= 0) {
		return board[index];
	}
	return 0;
}

void PlayField::drawBoard() {
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 10; x++) {
			std::cout << board[x + y * 10] << " ";
		}
		std::cout << std::endl;
	}
};

void PlayField::clearBoard() {
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 10; x++) {
			board[x + y * 10] = 0;
		}
	}
}

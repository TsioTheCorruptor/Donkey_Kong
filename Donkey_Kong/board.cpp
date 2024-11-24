#include <cstring>
#include <iostream>

#include "Board.h"

void Board::reset() {
	int i;
	std::cin >> i;
	if (i == 1) {
		for (int i = 0; i < MAX_Y; i++) {
			memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
		}
	}
	if (i == 2) {
		for (int i = 0; i < MAX_Y; i++) {
			memcpy(currentBoard[i], mainMenu[i], MAX_X + 1);
		}
	}
	
}

void Board::print() const {
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}
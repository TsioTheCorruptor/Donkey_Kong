#include <cstring>
#include <iostream>

#include "Board.h"
#include "healthManager.h"

void Board::reset() {
	//int i is just to check, not final
	int i=0;
//	std::cin >> i;
	//if (i == 1) {
		for (int i = 0; i < MAX_Y; i++) {
			memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
		}
		/*if (pHealth != nullptr) {
			delete pHealth;
		}
		if starting a new game
		if (pHealth == NULL) {
			pHealth = new Health();
			pHealth->resetHealth();
			pHealth->startedOrFinishedGame();
		}
		//if not
		else {
			pHealth->lowerHealth();
		}*/
	//}
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
	//pHealth->printHealth();
}




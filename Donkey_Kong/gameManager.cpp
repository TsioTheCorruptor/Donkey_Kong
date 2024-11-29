#include <cstring>
#include <iostream>

#include "gameManager.h"

void Game::resetGame() {

	pBoard = new Board();
	pBoard->reset();

	if (newGame == true) {
		health = MAX_HEALTH;
		newGame = false;
	}
	else {
		health = health - 1;
	}
}

void Game::printGame() {

	pBoard->print();
	printHealth();
}
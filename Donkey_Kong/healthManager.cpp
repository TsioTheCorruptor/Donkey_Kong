
#include <cstring>
#include <iostream>

#include "healthManager.h"

void Health::startedOrFinishedGame() {

	if (newGame) {
		newGame = false;
	}
	else {
		newGame = true;
	}
}

void Health::lowerHealth() {
	health = health - 1;
	if (health == 0) {
		//start over the game, game over screen etc...

	}
}

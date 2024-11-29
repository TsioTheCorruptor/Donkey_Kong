
#include <cstring>
#include <iostream>

#include "healthManager.h"

void Health::resetHealth() {

	health = MAX_HEALTH;

	/*for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentHealthDisplay[i], healthDisplay[i], MAX_X + 1);
	}*/
}

void Health::printHealth() const {

	draw(health);
	/*for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];*/
}

//activate this function when mario is either hit by a barrel or falls
void Health::lowerHealth() {
	health = health - 1;
	if (health == 0) {
		//start over the game, game over screen etc...

	}
	printHealth();

}

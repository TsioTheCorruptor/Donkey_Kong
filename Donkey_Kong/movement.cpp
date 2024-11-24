#include "movement.h"

void Pointmovement::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void Pointmovement::move() {
	int newX = x + dir.x;
	int newY = y + dir.y;
	// Better use a function in Board to check if the new position is valid
	// + Better use a constant for the wall character
	if (pBoard->getChar(newX, newY) == wall) {
		dir = { 0, 0 };
	}
	else {
		x = newX;
		y = newY;
	}
}

#include "Ghost.h"

//Function to check ghost collision
void Ghost::ghostCollision() {
	changeGhostsAligning(collisions);
}

//Function to change ghosts direction when colided with each other
void Ghost::changeGhostsAligning(const char colliders[]) {

	//Get chars to check for close ghosts
	char leftchar = pBoard->getChar(GetX() + 2, GetY());
	char rightchar = pBoard->getChar(GetX() - 2, GetY());
	//These chars are for if a barrel hits a wall or a ledge
	char leftchar2 = pBoard->getChar(GetX() + 1, GetY());
	char rightchar2 = pBoard->getChar(GetX() - 1, GetY());
	int newDirX = GetDirX() * -1;
	//Chcek for ghosts on the left
	if (GetDirX() == 1) {
		if (colliders[ghost] == leftchar || colliders[ghost] == leftchar2)
			set_dir(newDirX, 0, false);
	}
	//Chcek for ghosts on the right
	else {
		if (colliders[ghost] == rightchar || colliders[ghost] == rightchar2) {
			set_dir(newDirX, 0, false);
		}
	}
}
void Ghost::getGhostDir(const char colliders[]) {

	//Get the relevent chars for ghost collision detection
	char floorchar = pBoard->getChar(GetX(), GetY() + 1);
	char leftchar = pBoard->getChar(GetX() + 1, GetY());
	char rightchar = pBoard->getChar(GetX() - 1, GetY());
	char leftedge = pBoard->getChar(GetX() + 1, GetY() + 1);
	char rightedge = pBoard->getChar(GetX() - 1, GetY() + 1);

	//Enter this if only if it is a new ghost
	if (isSpanwed()) {
		//If there is a floor below the ghost, make it move right and activate it,
		//else, it will fall until reaching a floor
		if (colliders[floor_left] == floorchar || colliders[neutral_floor] == floorchar || colliders[floor_right] == floorchar) {
			set_dir(1, 0, false);
			setSpawned(false);
		}
	}

	//Define a new changed direction
	int newDirX = GetDirX() * -1;

	//Speacial case where the ghost cant move and thus stays still
	if ((leftedge == ' ' || leftchar == colliders[wall] || leftchar == colliders[ghost]) && (rightedge == ' ' || rightchar == colliders[wall] || rightchar == colliders[ghost])) {
		set_dir(0, 0, false);
	}
	//If there is a ledge, change dir
	else if (leftedge == ' ' || rightedge == ' ') {
		set_dir(newDirX, 0, false);
	}
	//If there is a wall, change dir
	else if (colliders[wall] == leftchar || colliders[wall] == rightchar) {
		set_dir(newDirX, 0, false);
	}

	//If none of the above happened, and the ghost is on floor, randomize its next direction
	else if (colliders[floor_left] == floorchar || colliders[neutral_floor] == floorchar || colliders[floor_right] == floorchar) {
		int chanceToChangeDir = std::rand() % 100;
		if (chanceToChangeDir > 95) {
			//THIS IS NOT GOOD, NEED SET_X AND SET_Y (MAYBE NOT IN EXERCISE 3)
			set_dir(newDirX, 0, false);
		}
	}

}

//This function checks the condition of the ghosts and prints them accordingly
void Ghost::checkAndMoveGhost() {

	//erase only if dir isnt 00,to avoid flickering
	if (!is_dir_0()) {
		erase();
	}
	getGhostDir(collisions);
	move(collisions, col_length);
}
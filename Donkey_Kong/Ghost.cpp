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
	//Check for ghosts on the left
	if (GetDirX() == 1) {
		if (colliders[ghost] == leftchar || colliders[ghost] == leftchar2)
			set_dir(newDirX, 0, false);
	}
	//Check for ghosts on the right
	else {
		if (colliders[ghost] == rightchar || colliders[ghost] == rightchar2) {
			set_dir(newDirX, 0, false);
		}
	}
}
void Ghost::getGhostDir(const char colliders[]) {

	//Get the relevent chars for ghost collision detection
	char leftchar = pBoard->getChar(GetX() + 1, GetY());
	char rightchar = pBoard->getChar(GetX() - 1, GetY());
	char leftedge = pBoard->getChar(GetX() + 1, GetY() + 1);
	char rightedge = pBoard->getChar(GetX() - 1, GetY() + 1);

	//Get an array of colliders for easier checks
	const char objectCol[] = { colliders[wall], colliders[ghost] };
	int objectColLen = 2;

	//If the direction is 0, make the ghost move right, then begin checking the other collisions
	if (GetDirX() == 0) {
		set_dir(1, 0, false);
	}

	//Enter this if only if it is a new ghost
	if (isSpawned()) {
		//If there is a floor below the ghost, make it move right and activate it,
		//else, it will fall until reaching a floor
		if (IsGrounded()) {
			set_dir(1, 0, false);
			setSpawned(false);
		}
	}
	                                                        
	//Define a new changed direction                        
	int newDirX = GetDirX() * -1;

	//Speacial case where the ghost cant move and thus stays still
	if ((IsCollidingGhostClass(objectCol, objectColLen, GetX() + 1, GetY()) || (leftedge == ' ')) && (IsCollidingGhostClass(objectCol, objectColLen, GetX() - 1, GetY()) || (rightedge == ' '))) {
		set_dir(0, 0, false);
	}
	
	//If the ghost moves left
	else if (GetDirX() == -1) {
		//If there is a ledge or a wall change dir
		if (rightedge == ' ' || colliders[wall] == rightchar) {
			set_dir(newDirX, 0, false);
		}
	}
	//If the ghost moves right
	else if (GetDirX() == 1) {
		//If there is a ledge or a wall change dir
		if (leftedge == ' ' || colliders[wall] == leftchar) {
			set_dir(newDirX, 0, false);
		}
	}
	
	//If none of the above happened, and the ghost is on floor, randomize its next direction
	else if (IsGrounded() && GetDirX() != 0) {
		int chanceToChangeDir = std::rand() % 100;
		if (chanceToChangeDir > 95) {
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

bool Ghost::IsCollidingGhostClass(const char colliders[], const int length, int Xpos, int Ypos){

	char toCheck = pBoard->getChar(Xpos, Ypos);
	for (int i = 0; i < length; i++){
		if (toCheck == colliders[i])
			return true;
	}
	return false;
}
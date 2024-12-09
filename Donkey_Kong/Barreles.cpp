#include "Barreles.h"

void Barrel::setTheBarrel(Barrel& barrel, Pointmovement& barrel_point, Board& board, int i) {

	barrel.set_barrel_char('O');
	barrel_point.set_movement_char(barrel.get_barrel_char());
	barrel_point.setBoard(board);
	barrel.SetPointMovement(barrel_point);
	barrel.SetBoard(board);
}
//This function checks the condition of the barrels and prints them accordingly
void Barrel::checkAndDrawBarrel(Barrel& barrel, Pointmovement& barrel_point) {

	//If the barrel didnt explode (and by that ended its life)
	if (!barrel.exploded) {
		barrel.getBarrelDir(barrel.collisions);
		barrel_point.draw();
		if (barrel.get_barrel_char() == '*') {
			barrel.exploded = true;
		}
	}
}

//Get the current direction of the barrel, also check if the distance fallen could cause an explosion
void Barrel::getBarrelDir(const char colliders[]) {

	//Get the char o
	char boardColToCheck = pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1);

	//If the barrel hits a '<' floor, move left and save its direction
	if (colliders[1] == boardColToCheck) {
		barrel_movement->set_dir(-1, 0);
		prev_dirX = -1;
		prev_dirY = 0;
		if (lengthFallen >= 8) {
			set_barrel_char('*');
		}
		lengthFallen = 0;
	}
	//If the barrel hits a '>' floor, move right and save its direction
	else if (colliders[3] == boardColToCheck) {
		barrel_movement->set_dir(1, 0);
		prev_dirX = 1;
		prev_dirY = 0;
		if (lengthFallen >= 8) {
			set_barrel_char('*');
		}
		lengthFallen = 0;
		//std::cout << "hit floor ";
	}
	//If the barrel hits a '=' floor, stay or move at the saved direction
	else if (colliders[2] == boardColToCheck){
		barrel_movement->set_dir(prev_dirX, prev_dirY);
		if (lengthFallen >= 8) {
			set_barrel_char('*');
		}
		lengthFallen = 0;
	}
	//If there is nothing below the barrel, increase the amount of characters fallen
	else if (' ' == boardColToCheck) {
		lengthFallen++;
	}
	char leftWall = pBoard->getChar(barrel_movement->GetX() + 1, barrel_movement->GetY());
	char rightWall = pBoard->getChar(barrel_movement->GetX() - 1, barrel_movement->GetY());
	//If the barrel hits a wall, return to the main x, y point
	if (colliders[0] == leftWall || colliders[0] == rightWall) {
		set_barrel_char('*');
	}
}

//Function  to erase and move the current barrel character
void Barrel::moveBarrel(Barrel& barrel, Pointmovement& barrel_point) {

	//this loop checks if the current barrel is on board and moves it accordingly
	if (!barrel.exploded) {
		//if the current barrel is on board, erase it (then draw it again next itteration)
		//erase the barrel character if its 'moving'
		if (!barrel_point.is_dir_0())
			barrel_point.erase();
		barrel_point.move(barrel.collisions, barrel.col_length);
		std::cout.flush();
	}
	//If the barrel exploded, erase its appearance
	else {
		barrel_point.erase();
	}
}
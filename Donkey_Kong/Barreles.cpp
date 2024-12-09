#include "Barreles.h"

void Barrel::setTheBarrel(Barrel& barrel, Pointmovement& barrel_point, Board& board, int i) {

	barrel.set_barrel_char('O');
	barrel_point.set_movement_char(barrel.get_barrel_char());
	barrel_point.setBoard(board);
	barrel.SetPointMovement(barrel_point);
	barrel.SetBoard(board);
	barrel.setWaitTime(5*i);

}
//This function checks the condition of the barrels and prints them accordingly
void Barrel::checkAndDrawBarrel(Barrel& barrel, Pointmovement& barrel_point) {

	//If the barrel didnt explode (and by that ended its life)
	if (!barrel.exploded) {
		barrel.getBarrelDir(barrel.collisions);
		//if the current 'i' barrel isnt yet on screen, lower the wait time (so eventually it will get to 0)
		if (barrel.getIsOnBoard() == false) {
			barrel.lowerWaitTime();
			//if the wait time is 0, the barrel will be able to be displayed on the board
			if (barrel.canBeThrown()) {
				barrel.throwBarrel();
			}
		}
		//if the barrel is able to be displayed on the board, print its character
		if (barrel.getIsOnBoard())
			barrel_point.draw();

		if (barrel.get_barrel_char() == '*') {
			barrel.exploded = true;
		}
	}
}

//Get the current direction of the barrel, also check if the distance fallen could cause an explosion
void Barrel::getBarrelDir(const char colliders[]) {

	//If the barrel hits a '<' floor, move left and save its direction
	if (colliders[1] == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)) {
		barrel_movement->set_dir(-1, 0);
		prev_dirX = -1;
		prev_dirY = 0;
		if (lengthFallen >= 8) {
			set_barrel_char('*');
		}
		lengthFallen = 0;
	}
	//If the barrel hits a '>' floor, move right and save its direction
	else if (colliders[3] == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)) {
		barrel_movement->set_dir(1, 0);
		prev_dirX = 1;
		prev_dirY = 0;
		if (lengthFallen >= 8) {
			set_barrel_char('*');
		}
		lengthFallen = 0;
	}
	//If the barrel hits a '=' floor, stay or move at the saved direction
	else if (colliders[2] == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)){
		barrel_movement->set_dir(prev_dirX, prev_dirY);
		if (lengthFallen >= 8) {
			set_barrel_char('*');
		}
		lengthFallen = 0;
	}
	//If there is nothing below the barrel, increase the amount of characters fallen
	else if (' ' == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)) {
		lengthFallen++;
	}
	//If the barrel hits a wall, return to the main x, y point
	if (barrel_movement->IsColliding(colliders,col_length,barrel_movement->GetX()+barrel_movement->GetDirX(), barrel_movement->GetY()) || barrel_movement->IsColliding(colliders, col_length, barrel_movement->GetX() + barrel_movement->GetDirX(), barrel_movement->GetY())) {
		barrel_movement->SetPos(9, 3);
	}
}

//Function  to erase and move the current barrel character
void Barrel::moveBarrel(Barrel& barrel, Pointmovement& barrel_point) {
	//this loop checks if the current barrel is on board and moves it accordingly
	if (!barrel.exploded) {
		//if the current barrel is on board, erase it (then draw it again next itteration)
		if (barrel.getIsOnBoard()) {
			//erase the barrel character if its 'moving'
			if (!barrel_point.is_dir_0())
				barrel_point.erase();
			barrel_point.move(barrel.collisions, barrel.col_length);
			std::cout.flush();
		}
	}
	//If the barrel exploded, delete it completly
	else {
		barrel_point.erase();
	}
	
}
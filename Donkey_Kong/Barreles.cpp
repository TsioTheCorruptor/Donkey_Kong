#include "Barreles.h"

void Barreles::setTheBarreles(Barreles barrel[], Pointmovement barrel_point[], Board board) {
	for (int i = 0; i < 10; i++) {
		barrel[i].set_barrel_char('O');
		barrel_point[i].set_movement_char(barrel[i].get_barrel_char());
		barrel_point[i].setBoard(board);
		barrel[i].SetPointMovement(barrel_point[i]);
		barrel[i].SetBoard(board);
		barrel[i].setWaitTime(i * 10);
	}
}

//This function checks the condition of the barrels and prints them accordingly
void Barreles::checkAndDrawBarreles(Barreles barrel[], Pointmovement barrel_point[]) {
	//the loop of drawing the current barrels
	for (int i = 0; i < 10; i++) {
		//If the barrel didnt explode (and by that ended its life)
		if (!barrel[i].exploded) {
			barrel[i].getBarrelDir(barrel[i].collisions);
			//if the current 'i' barrel isnt yet on screen, lower the wait time (so eventually it will get to 0)
			if (barrel[i].getIsOnBoard() == false) {
				barrel[i].lowerWaitTime();
				//if the wait time is 0, the barrel will be able to be displayed on the board
				if (barrel[i].canBeThrown()) {
					barrel[i].throwBarrel();
				}
			}
			//if the barrel is able to be displayed on the board, print its character
			if (barrel[i].getIsOnBoard())
				barrel_point[i].draw();

			if (barrel[i].get_barrel_char() == '*') {
				barrel[i].exploded = true;
			}
		}
	}
}

//Get the current direction of the barrel, also check if the distance fallen could cause an explosion
void Barreles::getBarrelDir(const char colliders[]) {

	//If the barrel hits a '<' floor, move left and save its direction
	if (colliders[1] == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)) {
		barrel_movement->set_dir(-1, 0);
		prev_dirX = -1;
		prev_dirY = 0;
		if (amountFallen >= 8) {
			set_barrel_char('*');
		}
		amountFallen = 0;
	}
	//If the barrel hits a '>' floor, move right and save its direction
	else if (colliders[3] == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)) {
		barrel_movement->set_dir(1, 0);
		prev_dirX = 1;
		prev_dirY = 0;
		if (amountFallen >= 8) {
			set_barrel_char('*');
		}
		amountFallen = 0;
	}
	//If the barrel hits a '=' floor, stay or move at the saved direction
	else if (colliders[2] == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)){
		barrel_movement->set_dir(prev_dirX, prev_dirY);
		if (amountFallen >= 8) {
			set_barrel_char('*');
		}
		amountFallen = 0;
	}
	//If there is nothing below the barrel, increase the amount of characters fallen
	else if (' ' == pBoard->getChar(barrel_movement->GetX(), barrel_movement->GetY() + 1)) {
		amountFallen++;
	}
}

//Function  to erase and move the current barrel character
void Barreles::moveBarreles(Barreles barrel[], Pointmovement barrel_point[]) {
	//this loop checks if the current barrel is on board and moves it accordingly
	for (int i = 0; i < 10; i++) {
		if (!barrel[i].exploded) {
			//if the current barrel is on board, erase it (then draw it again next itteration)
			if (barrel[i].getIsOnBoard()) {
				//erase the barrel character if its 'moving'
				if (!barrel_point[i].is_dir_0())
					barrel_point[i].erase();
				barrel_point[i].move(barrel[i].collisions, barrel[i].col_length);
				std::cout.flush();
			}
		}
		//If the barrel exploded, delete it completly
		else {
			barrel_point[i].erase();
		}
	}
}
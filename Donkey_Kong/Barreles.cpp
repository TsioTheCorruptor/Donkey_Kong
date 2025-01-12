#include "Barreles.h"

//This function checks the condition of the barrels and prints them accordingly
void Barrel::checkAndMoveBarrel() {
	//erase only if dir isnt 00,to avoid flickering
	if (!is_dir_0()){
		erase();
	}
		
	//If the barrel didnt fully explode (and by that ended its life)
	if (!explosion_ended) {
		getBarrelDir(collisions);

		if (!stop_movement)
			move(collisions,col_length);
	
		if (get_barrel_char() == explosion_char) {
			explosion_started = true;
			if (explode_stage >= explode_delay)
				explosion_ended = true;
			else
				explode_stage++;
		}
	}
	//making sure that after an explosion,any background char will not be affected
	else { 
        SetMovementChar(pBoard->getOgChar(GetX(),GetY()));
		draw();
	}
}

//Get the current direction of the barrel, also check if the distance fallen could cause an explosion
void Barrel::getBarrelDir(const char colliders[]) {

	//Get the relevent chars for barrel collision detection
	char floorchar = pBoard->getChar(GetX(), GetY() + 1);
	char leftchar = pBoard->getChar(GetX() + 1, GetY());
	char rightchar = pBoard->getChar(GetX() - 1, GetY());

	//If the barrel hits a '<' floor, move left and save its direction
	if (colliders[floor_left] == floorchar) {
		set_dir(-1, 0, false);
		prev_dirX = -1;
		prev_dirY = 0;
		if (GetAirTime() >= 8) {
			stop_movement = true;
			set_barrel_char(explosion_char);
			SetMovementChar(explosion_char);
		}
	}
	//If the barrel hits a '>' floor, move right and save its direction
	else if (colliders[floor_right] == floorchar) {
		set_dir(1, 0,false);
		prev_dirX = 1;
		prev_dirY = 0;
		if (GetAirTime() >= 8) {
			stop_movement = true;
			set_barrel_char(explosion_char);
			SetMovementChar(explosion_char);
		}
	}
	//If the barrel hits a '=' floor, stay or move at the saved direction
	else if (colliders[neutral_floor] == floorchar){
		if(prev_dirX!=0)
		set_dir(prev_dirX, prev_dirY,false);
		else{
			//if no floor was hit before,hence the dir is 00, set dir to 10 by default
			set_dir(1, 0,false);
			prev_dirX = 1;
			prev_dirY = 0;
		}	
		if (GetAirTime() >= 8) {
			stop_movement = true;
			set_barrel_char(explosion_char);
			SetMovementChar(explosion_char);
		}
	}
	//if barrel hits wall,it explodes
	if (colliders[wall] == leftchar || colliders[wall] == rightchar) {
		stop_movement = true;
		set_barrel_char(explosion_char);
		SetMovementChar(explosion_char);
	}
}
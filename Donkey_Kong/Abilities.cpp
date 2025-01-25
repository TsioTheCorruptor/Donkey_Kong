
#include "Abilities.h"

bool Abilities::InLadder(Pointmovement* objcet_movement) {
	//if going up the ladder
	//move up until detecting ceiling(collider above the entity)
	bool toReturn = true;
	if (ladder_up) {
		bool detected_ceiling = objcet_movement->IsColliding(collisions, col_length, objcet_movement->GetX(), objcet_movement->GetY() - 1);
		if (detected_ceiling) {
			toReturn = false;
			//move two points up to get above floor(if possible)
			objcet_movement->set_dir(0, -2, true);
			objcet_movement->move(collisions, col_length);
			//stop moving after going up
			objcet_movement->set_dir(0, 0, false);
		}
		else objcet_movement->set_dir(0, -1, true);
	}
	//if going down ladder
	if (!ladder_up) {
		bool detected_ground = false;
		//go two points down to go below floor
		if (go_below_ground == false) {
			detected_ground = objcet_movement->IsColliding(collisions, col_length, objcet_movement->GetX(), objcet_movement->GetY() + 2);
			objcet_movement->set_dir(0, 2, false);
			go_below_ground = true;
		}
		//after going below ground once,go down until ground
		else {
			detected_ground = objcet_movement->IsCollidingInGround(collisions, col_length);
			objcet_movement->set_dir(0, 1, true);
		}

		//if ground is detected,stop going down ladder
		if (detected_ground) {
			toReturn = false;
			objcet_movement->set_dir(0, 0, false);
			go_below_ground = false;
		}
	}

	return toReturn;
}
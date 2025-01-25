#pragma once

#include "movement.h"

class Abilities {

	bool ladder_up = true; //going up or down ladder
	bool go_below_ground = false;
	static constexpr char collisions[4] = { 'Q','<','=','>' }; //mario/ghost collisions
	static constexpr int col_length = 4;

public:
	
	Abilities(bool ladderUp, bool goBelowGround) :
		ladder_up(ladderUp), go_below_ground(goBelowGround) {}

	bool InLadder(Pointmovement* objcet_movement);
	const char* GetCollisionArray()const { return collisions; }
	const int GetCollisionArrayLength()const { return col_length; }

	void set_ladder_up(bool set) {
		ladder_up = set;
	}
};
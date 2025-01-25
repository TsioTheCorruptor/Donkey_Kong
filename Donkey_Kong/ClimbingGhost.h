#pragma once

#include "Ghost.h"
#include "abilities.h"

class ClimbingGhost : public Ghost {

	bool is_climbing = false;
	//The climbing ghost contains abilities class so it will be able to chase Mario by climbing ladders
	Abilities ghost_abilities;
	//The ghost also needs the pointmovement of Mario inorder to chase him
	Pointmovement* player_movement = nullptr;

public:

	ClimbingGhost(const char move_char, int posx, int posy, Board& board, char player_char, Pointmovement& player_Movement, Abilities ghost_abilities) :
		Ghost(move_char, posx, posy, board, player_char), player_movement(&player_Movement), ghost_abilities(ghost_abilities) {
		ghost_char = 'X';
	}

	bool isClimbing() const{
		return is_climbing;
	}

	void setClimbing(bool set) {
		is_climbing = set;
	}

	virtual void checkAndMoveGhost();

};

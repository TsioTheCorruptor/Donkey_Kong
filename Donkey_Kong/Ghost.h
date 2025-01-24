#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"
#include <stdbool.h>

class Ghost : public Pointmovement {

	char ghost_char = 'x';
	char playerChar = '@';
	Board* pBoard = nullptr;
	bool spawned = true;
	static constexpr char collisions[] = { '@','Q','<','=','>','x'};
	static constexpr  int col_length = 6;
	enum class coll_hit { player, wall, floor_left, neutral_floor, floor_right, ghost};//order has to stay
	
public:

	Ghost(const char move_char, int posx, int posy, Board& board, char player_char) :
		Pointmovement(move_char, posx, posy, board), pBoard(&board),playerChar(player_char ) {}

	void checkAndMoveGhost();

	void getGhostDir(const char colliders[]);

	const char get_ghost_char() const {
		return ghost_char;
	}

	void set_ghost_char(const char chr) {
		ghost_char = chr;
	}

	void setSpawned(bool set) {
		spawned = set;
	}

	bool isSpawned() const {
		return spawned;
	}

	void ghostCollision();

	void changeGhostsAligning(const char colliders[]);

	bool IsCollidingGhostClass(const char colliders[], int length, int xpos, int ypos) const;

	bool checkGhostHit(Pointmovement mario) const;
};

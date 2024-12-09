#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"

class Barrel {

	char barrel_char = 'O';
	Pointmovement* barrel_movement = nullptr;
	Board* pBoard = nullptr;
	int prev_dirX;
	int prev_dirY;
	int lengthFallen;
	bool exploded;
	

 public:
	Barrel() : prev_dirX(0), prev_dirY(0), lengthFallen(0), exploded(false) {}

	static constexpr char collisions[4] = { 'Q','<','=','>' };

	int col_length = 4;

	void setTheBarrel(Barrel& barrel, Pointmovement& barrel_point, Board& board, int i);

	void checkAndDrawBarrel(Barrel& barrel, Pointmovement& barrel_point);

	void moveBarrel(Barrel& barrel, Pointmovement& barrel_point);

	char get_barrel_char() {
		return barrel_char;
	}
	void set_barrel_char(const char chr) {
		barrel_char = chr;
	}
	void SetPointMovement(Pointmovement& pm_) {
		barrel_movement = &pm_;
	}
	void SetBoard(Board& _board) {
		pBoard = &_board;
	}
	void getBarrelDir(const char colliders[]);

	bool isExploded() {
		return exploded;
	}
};
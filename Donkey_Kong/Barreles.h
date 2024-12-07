#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"

class Barrel {

	char barrel_char = 'O';
	Pointmovement* barrel_movement = nullptr;
	Board* pBoard = nullptr;
	static constexpr int barrelsAmount = 20; //maybe in main? outside of this class?
	int prev_dirX;
	int prev_dirY;
	int waitTime;     
	bool isOnBoard;
	int lengthFallen;
	bool exploded;

 public:

	Barrel() : prev_dirX(0), prev_dirY(0), waitTime(0), isOnBoard(false), lengthFallen(0), exploded(false) {}

	static constexpr char collisions[4] = { 'Q','<','=','>' };

	int col_length = 4;

	//maybe outside of this class?
	static constexpr int getBarrelsAmount() {
		return barrelsAmount;
	}

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

	void setWaitTime(int w) {
		waitTime = w;
	}
	void lowerWaitTime() {
		if (waitTime > 0)
			waitTime--;
	}
	bool canBeThrown() {
		return waitTime == 0;
	}
	void throwBarrel() {
		isOnBoard = true;
	}
	bool getIsOnBoard() {
		return isOnBoard;
	}
};
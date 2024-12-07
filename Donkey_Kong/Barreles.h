#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"

class Barreles {

	char barrel_char = 'O';
	Pointmovement* barrel_movement = nullptr;
	Board* pBoard = nullptr;
	int prev_dirX;
	int prev_dirY;
	int waitTime;     
	bool isOnBoard;
	int amountFallen;
	bool exploded;

 public:
	Barreles() : prev_dirX(0), prev_dirY(0), waitTime(0), isOnBoard(false), amountFallen(0), exploded(false) {}
	static constexpr char collisions[4] = { 'Q','<','=','>' };
	int col_length = 4;

	void setTheBarreles(Barreles barrel[], Pointmovement barrel_point[], Board board);

	void checkAndDrawBarreles(Barreles barrel[], Pointmovement barrel_point[]);

	void moveBarreles(Barreles barrel[], Pointmovement barrel_point[]);

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
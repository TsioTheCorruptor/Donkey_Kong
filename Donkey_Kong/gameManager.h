#pragma once

#include <iostream>

#include "utils.h"
#include "board.h"
#define MAX_HEALTH 3

class Game {
	/*static constexpr int MAX_X = 4;
	static constexpr int MAX_Y = 3;
	static constexpr int MAX_Z = 3;*/
	int healthPosX = 75;
	int healthPosY = 2;
	int health = MAX_HEALTH;
	bool newGame = true;

	/*const char* healthDisplay[MAX_Y][MAX_Z] = {
		{" __ ",
		 " __|",
		 " __|"},
		{" __ ",
		 " __|",
		 "|__ "},
		{"  |",
		 "  |",
		 "  |",}
	};
	char currentHealthDisplay[MAX_Y][MAX_X + 1]; // +1 for null terminator*/
	Board* pBoard = nullptr;
public:

	void draw(int c)  const {
		gotoxy(healthPosX, healthPosY);
		std::cout << c;
		std::cout.flush();
	}
	void resetGame();
	void resetHealth();
	void lowerHealth();
	void printGame();
	void printHealth() const {
		draw(health);
	}
	void getCharInBoard(int x, int y, char into) {
		into = pBoard->getChar(x, y);
	}
	/*char getChar(int x, int y) const {
		return currentBoard[y][x];
	}*/
};
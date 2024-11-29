#pragma once

#include <iostream>

#include "utils.h"
#define MAX_HEALTH 3

class Health {
	/*static constexpr int MAX_X = 4;
	static constexpr int MAX_Y = 3;
	static constexpr int MAX_Z = 3;*/
	int healthPosX = 75;
	int healthPosY = 2;
	int health = MAX_HEALTH;

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

public:
	void draw(int c)  const {
		gotoxy(healthPosX, healthPosY);
		std::cout << c;
		std::cout.flush();
	}
	void resetHealth();
	void lowerHealth();
	void printHealth() const;
	/*char getChar(int x, int y) const {
		return currentBoard[y][x];
	}*/

};

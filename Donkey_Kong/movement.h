#pragma once
#pragma once

#include <iostream>

#include "utils.h"
#include "Board.h"

class Pointmovement {
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x = 20, y = 23;
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	char ch = '@';
	const char wall = 'Q';
	Board* pBoard = nullptr;
	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}
public:
	void draw() const {
		draw(ch);
	}
	void erase() {
		draw(' ');
	}
	void keyPressed(char key);
	void move();
	void setBoard(Board& board) {
		pBoard = &board;
	}
};


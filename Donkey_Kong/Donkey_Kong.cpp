// Donkey_Kong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "movement.h"

// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Pointmovement p;
	p.setBoard(board);
	board.reset();
	board.print();
	while (true) {
		p.draw();
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) break;
			p.keyPressed(key);
		}
		Sleep(50);
		p.erase();
		p.move();
	}
}



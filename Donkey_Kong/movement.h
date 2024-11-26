#pragma once

#include <iostream>

#include "utils.h"
#include "board.h"
#include "Mario.h"
class Pointmovement {
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x =1, y =1;
	int prevx = 1, prevy = 1;

	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	 char ch ;
	 char prev_char;
	
	Board* pBoard = nullptr;
	void draw(char c)  {//removed const
		gotoxy(x, y);
		std::cout << c;
	}
	bool IsColliding(const char colliders[], int length,int xpos,int ypos);
	
	
public:
	void draw()
	{//removed const
		draw(ch);
		
	}
	void erase() {
		draw(' ');
	}
	void keyPressed(char key);
	void move(const char colliders[], int length);
	void setBoard(Board& board) {
		pBoard = &board;
	}
	void set_movement_char( char chr)
	{
		ch = chr;
	}
	void set_prev_movement_char(char chr)
	{
		prev_char = chr;
	}
	void draw_InPosition(int xpos, int ypos, char chr)
	{
		gotoxy(xpos, ypos);
		std::cout << chr;
	}
};


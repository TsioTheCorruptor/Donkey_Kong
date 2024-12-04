#pragma once

#include <iostream>

#include "utils.h"
#include "board.h"
#include "Mario.h"
#include "gameManager.h"
class Pointmovement {
	static constexpr char keys[] = {  'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = {  {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x =10, y =1;
	int prevx = 1, prevy = 1;

	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	 char ch ;
	 char prev_char;
	 bool overwrite_gravity = false;
	Board* pBoard = nullptr;
	//Game* pGame = nullptr;
	void draw(char c)  {//removed const
		gotoxy(x, y);
		std::cout << c;
		std::cout.flush();
	}
	
	
	
public:
bool IsColliding(const char colliders[], int length,int xpos,int ypos);

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
	/*void setGame(Game& game) {
		pGame = &game;
	}*/
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
	bool is_dir_0();
	void set_dir(int dirx, int diry)
	{
		dir.x = dirx;
		dir.y = diry;
		overwrite_gravity = true;
	}
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
	int GetDirX()
	{
		return dir.x;
	}
	int GetDirY()
	{
		return dir.y;
	}
	
};


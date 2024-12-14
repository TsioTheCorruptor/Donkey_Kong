#pragma once

#include <iostream>

#include "utils.h"
#include "board.h"
//#include "Mario.h"
//#include "gameManager.h"
class Pointmovement {
	static constexpr char keys[] = {  'a', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = {  {-1, 0}, {1, 0}, {0, 0} };
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	int x =9, y =3;
	int prevx = 1, prevy = 1;
	bool keep_momentum = false;
	bool keep_momentum_always = true;
	
	 char movement_char=' ';
	 char prev_char=' ';
	 bool overwrite_gravity = true;
	 bool Grounded = false;
	Board* pBoard = nullptr;
	
	void draw(char c)  {//removed const
		pBoard->draw_InPosition(x, y, c);
		//gotoxy(x, y);
		//std::cout << c;

		
	}
	
	
	
public:
	Pointmovement(const char move_char, int posx, int posy, Board& board) : movement_char(move_char), x(posx), y(posy), pBoard(&board) {}
	
	
	
	
	

bool IsColliding(const char colliders[], int length,int xpos,int ypos);
bool IsCollidingInNextDir(const char colliders[], int length) ;
bool IsCollidingInGround(const char colliders[], int length);
bool IsGrounded()
{
	return Grounded;
}
	void draw()
	{//removed const
		draw(movement_char);
		
	}
	void erase() {
		draw(' ');
	}
	void keyPressed(char key);
	void move(const char colliders[], int length);
	void SetPos(int posx, int posy);
	void setBoard(Board& board) {
		pBoard = &board;
	}
	/*void setGame(Game& game) {
		pGame = &game;
	}*/
	void set_movement_char( char chr)
	{
		movement_char = chr;
	}
	void set_prev_movement_char(char chr)
	{
		prev_char = chr;
	}
	/*void draw_InPosition(int xpos, int ypos, char chr)
	{
		gotoxy(xpos, ypos);
		std::cout << chr;
		pBoard->setChar(xpos, ypos, chr);
	}*/
	bool is_dir_0();
	void set_dir(int dirx, int diry,bool overwrite_grav)
	{
		dir.x = dirx;
		dir.y = diry;
		if (overwrite_grav)
			overwrite_gravity = true;
		else
			overwrite_gravity = false;
	}
	const int GetX() const
	{
		return x;
	}
	const int GetY() const
	{
		return y;
	}
	const int GetDirX() const
	{
		return dir.x;
	}
	const int GetDirY() const
	{
		return dir.y;
	}
	const char GetCurrentBackgroundChar() const
	{
		return pBoard->getOgChar(x,y);
	}
	
	const char GetPrevChar() const
	{
		return prev_char;
	}
	 void SetPrevChar() 
	{
		 prev_char=pBoard->getChar(x,y);
	}
};


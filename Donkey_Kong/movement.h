#pragma once

#include <iostream>

#include "utils.h"
#include "board.h"

class Pointmovement {
	static constexpr char keys[] = {  'a', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = {  {-1, 0}, {1, 0}, {0, 0} };
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	int x =9, y =3;
	
	bool keep_momentum_always =true;//allow movement in air,no matter what
	bool keep_momentum = false;//allow for single iteration

	 char movement_char=' ';
	 char prev_char=' ';//char that the point passed trough
	 bool overwrite_gravity = true;//ignore gravity
	 bool Grounded = false;
	 int iterations_in_air = 0;
	 
	Board* pBoard = nullptr;
	
	void draw(char c)const  {
		pBoard->draw_InPosition(x, y, c);
	}
	
	
	
public:
	Pointmovement(const char move_char, int posx, int posy, Board& board) : movement_char(move_char), x(posx), y(posy), pBoard(&board) {}
	
	
	
bool IsColliding(const char colliders[], int length,int xpos,int ypos);
bool IsCollidingInNextDir(const char colliders[], int length) ;
bool IsCollidingInGround(const char colliders[], int length);
bool is_dir_0();
void keyPressed(char key);
void move(const char colliders[], int length);
void SetPos(int posx, int posy);


bool IsGrounded()
{
	return Grounded;
}
	void draw()const
	{
		draw(movement_char);
		
	}
	void erase() {
		draw(' ');
	}
	
	void SetMovementChar(char chr)
	{
		movement_char = chr;
	}
	void set_prev_movement_char(char chr)
	{
		prev_char = chr;
	}
	
	void set_dir(int dirx, int diry,bool overwrite_grav)
	{
		dir.x = dirx;
		dir.y = diry;
		overwrite_gravity = overwrite_grav;
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
	 const int GetAirTime() const
	 {
		 return iterations_in_air;
	}
};


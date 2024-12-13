#pragma once
#include <iostream>
#include "movement.h"
#include "board.h"

class Mario {


 char mario_char = '@';
 struct Jump_InOrder { int x, y; };
 bool go_below_ground = false;
 
 int move_stage = 0;

 static constexpr Jump_InOrder jump_inorder_right[] = { {0, -1}, {1, -1},{1,0},{1,1}, {0,1} };
 int move_count_right = 5;

 static constexpr Jump_InOrder jump_inorder_left[] = { {0, -1}, {-1, -1},{-1,0}, {-1, 1}, {0,1}};
 int move_count_left = 5;

 static constexpr Jump_InOrder jump_inorder_neutral[] = { {0, -1},{0, -1} };
 int move_count_neutral = 2;

 bool isjumping = false;
 bool ladder_up = true;
 Pointmovement* pm = nullptr;
 Board* board = nullptr;

public:
	Jump_InOrder currdir = { 0,0 };
	
static constexpr char collisions[4] = { 'Q','<','=','>'};
int col_length = 4;
enum move_type {no_moves,jumping,ladder};
	move_type curr_move = no_moves;

	
	 char  get_mario_char()
	{
		return mario_char;
	}
	void  set_mario_char(const char chr)
	{
		mario_char=chr;
	}
	void SetPointMovement(Pointmovement& pm_)
	{
		pm = &pm_;
	}
	
	void SetBoard(Board& _board)
	{
		board = &_board;
	}
	void Jump();
	void InLadder();

	void Jump_InDirection(const Jump_InOrder* order, int length,int currdirx,int currdiey);
	bool is_jumping()
	{
		return isjumping;
	}
	int GetMoveType(char key);

};
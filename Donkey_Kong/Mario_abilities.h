#pragma once
#include <iostream>
#include "movement.h"
#include "board.h"
class Mario_abilities
{
	struct Jump_InOrder { int x, y; };
	static constexpr Jump_InOrder jump_inorder_right[] = { {0, -1}, {1, -1}, {1, 1}, {0,1} };
	int move_count_right = 4;
	static constexpr Jump_InOrder jump_inorder_left[] = { {0, -1}, {-1, -1}, {-1, 1}, {0,1} };
	int move_count_left = 4;
	static constexpr Jump_InOrder jump_inorder_neutral[] = { {0, -1},{0, -1} };
	int move_count_neutral = 2;
	bool jumping = false;
	bool ladder_up = true;
	Pointmovement* pm=nullptr;
	unsigned int move_type=0;
	Mario* player = nullptr;
	Board* board = nullptr;
	

public:

void SetPointMovement(Pointmovement& pm_)
	{
		pm = &pm_;
	}
void SetMario(Mario& mario)
{
	player = &mario;
}
void SetBoard(Board& _board)
{
	board = &_board;
}
void Jump();
void InLadder();

void Jump_InDirection(const Jump_InOrder* order,int length);
bool is_jumping()
{
	return jumping;
}
int GetMoveType(char key);

};
#pragma once
#include <iostream>
#include "movement.h"
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
	Pointmovement* pm;
	
	

public:

void SetPointMovement(Pointmovement& pm_)
	{
		pm = &pm_;
	}
void Jump();
void Jump_InDirection(const Jump_InOrder* order,int length);
bool is_jumping()
{
	return jumping;
}
};
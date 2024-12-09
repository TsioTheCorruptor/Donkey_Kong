#include "Mario.h"
void  Mario::Jump_InDirection(const Jump_InOrder* order, int length, int currdirx, int currdiry) {
	curr_move=jumping;
	isjumping = true;
	
	pm->set_dir(order[move_stage].x, order[move_stage].y);
	move_stage++;
	if (move_stage >= length||pm->IsCollidingInNextDir(collisions,col_length))
	{
		
		move_stage = 0;
		curr_move=no_moves;
		isjumping = false;

	}

}
void  Mario::Jump()
{
	
	if (!isjumping)
	{
		currdir.x = pm->GetDirX();
		currdir.y = pm->GetDirY();
	}

	if (currdir.x == 1 && currdir.y == 0)
		Jump_InDirection(jump_inorder_right, move_count_right, currdir.x, currdir.y);

	if (currdir.x == -1 && currdir.y == 0)
		Jump_InDirection(jump_inorder_left, move_count_left, currdir.x, currdir.y);

	if (currdir.x == 0 && currdir.y == 0)
		Jump_InDirection(jump_inorder_neutral, move_count_neutral,currdir.x, currdir.y);
}



int  Mario::GetMoveType(char key)
{
	bool isgrounded = pm->IsColliding(collisions, col_length, pm->GetX(), pm->GetY() + 1);
	if (key == 'w' && isgrounded)
	{
		curr_move=jumping;
	}
	if (key == 'w' && isgrounded && pm->GetCurrentBackgroundChar() =='H')
	{
		ladder_up = true;
		curr_move=ladder;
	}
	if (key == 'x' && isgrounded && board->getChar(pm->GetX(), pm->GetY() + 2) == 'H')
	{
		ladder_up = false;
		curr_move=ladder;
	}
	return curr_move;
}


void Mario::InLadder()
{

	if (ladder_up)
	{
		bool detected_ceiling = pm->IsColliding(collisions, col_length, pm->GetX(), pm->GetY() - 1);

		if (detected_ceiling)
		{
			curr_move=no_moves;
			pm->set_dir(0, -2);
			pm->move(collisions,col_length);
			pm->set_dir(0, 0);
		}
		else pm->set_dir(0, -1);
	}
	if (!ladder_up)
	{
		
		bool detected_ground = false;
		if (go_below_ground == false)
		{
			detected_ground = pm->IsColliding(collisions, col_length, pm->GetX(), pm->GetY() + 2);
			pm->set_dir(0, 2);
			go_below_ground = true;
		}
		else
		{
			detected_ground = pm->IsColliding(collisions, col_length, pm->GetX(), pm->GetY() + 1);
			pm->set_dir(0, 1);
		}


		if (detected_ground)
		{
			curr_move=no_moves;
			pm->set_dir(0, 0);
			go_below_ground = false;

		}
	}
}
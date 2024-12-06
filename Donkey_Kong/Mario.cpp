#include "Mario.h"
void  Mario::Jump_InDirection(const Jump_InOrder* order, int length) {
	curr_move=jumping;
	isjumping = true;
	static int move_stage = 0;
	pm->set_dir(order[move_stage].x, order[move_stage].y);
	move_stage++;
	if (move_stage >= length)
	{
		move_stage = 0;
		curr_move=no_moves;
		isjumping = false;

	}

}
void  Mario::Jump()
{
	static Jump_InOrder currdir;
	if (!isjumping)
	{
		currdir.x = pm->GetDirX();
		currdir.y = pm->GetDirY();
	}

	if (currdir.x == 1 && currdir.y == 0)
		Jump_InDirection(jump_inorder_right, move_count_right);

	if (currdir.x == -1 && currdir.y == 0)
		Jump_InDirection(jump_inorder_left, move_count_left);

	if (currdir.x == 0 && currdir.y == 0)
		Jump_InDirection(jump_inorder_neutral, move_count_neutral);
}



int  Mario::GetMoveType(char key)
{
	bool isgrounded = pm->IsColliding(collisions, col_length, pm->GetX(), pm->GetY() + 1);
	if (key == 'w' && isgrounded)
	{
		curr_move=jumping;
	}
	if (key == 'w' && isgrounded && pm->GetCurrentBackgroundChar() == 'H')
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
		static bool once = false;
		bool detected_ground = false;
		if (once == false)
		{
			detected_ground = pm->IsColliding(collisions, col_length, pm->GetX(), pm->GetY() + 2);
			pm->set_dir(0, 2);
			once = true;
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
			once = false;

		}
	}
}
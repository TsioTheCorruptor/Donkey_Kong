#include "Mario.h"
void  Mario::Jump_InDirection(const Jump_InOrder* order, int length, int currdirx, int currdiry) {
	curr_move=jumping;
	isjumping = true;
	
	player_movement->set_dir(order[move_stage].x, order[move_stage].y,true);
	move_stage++;
	if (move_stage >= length|| player_movement->IsCollidingInNextDir(collisions,col_length))
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
		savedirX = player_movement->GetDirX();
		savedirY = player_movement->GetDirY();
	}

	if (savedirX == 1 && savedirY == 0)
		Jump_InDirection(jump_inorder_right, move_count_right, savedirX, savedirY);

	if (savedirX == -1 && savedirY == 0)
		Jump_InDirection(jump_inorder_left, move_count_left, savedirX, savedirY);

	if (savedirX == 0 && savedirY == 0)
		Jump_InDirection(jump_inorder_neutral, move_count_neutral, savedirX, savedirY);
}



int  Mario::GetMoveType(char key)
{
	key = tolower(key);
	bool isgrounded = player_movement->IsColliding(collisions, col_length, player_movement->GetX(), player_movement->GetY() + 1);
	if (key == upkey && isgrounded)
	{
		curr_move=jumping;
	}
	if (key == upkey && isgrounded && player_movement->GetCurrentBackgroundChar() ==ladder_char)
	{
		ladder_up = true;
		curr_move=ladder;
	}
	if (key == downkey && isgrounded && board->getOgChar(player_movement->GetX(), player_movement->GetY() + 2) == 'H')
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
		bool detected_ceiling = player_movement->IsColliding(collisions, col_length, player_movement->GetX(), player_movement->GetY() - 1);

		if (detected_ceiling)
		{
			curr_move=no_moves;
			player_movement->set_dir(0, -2,true);
			player_movement->move(collisions,col_length);
			player_movement->set_dir(0, 0,false);
		}
		else player_movement->set_dir(0, -1,true);
	}
	if (!ladder_up)
	{
		
		bool detected_ground = false;
		if (go_below_ground == false)
		{
			detected_ground = player_movement->IsColliding(collisions, col_length, player_movement->GetX(), player_movement->GetY() + 2);
			player_movement->set_dir(0, 2,false);
			go_below_ground = true;
		}
		else
		{
			detected_ground = player_movement->IsColliding(collisions, col_length, player_movement->GetX(), player_movement->GetY() + 1);
			player_movement->set_dir(0, 1,true);
		}


		if (detected_ground)
		{
			curr_move=no_moves;
			player_movement->set_dir(0, 0,false);
			go_below_ground = false;

		}
	}
}
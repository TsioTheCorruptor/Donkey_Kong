#include "Mario_abilities.h"
void  Mario_abilities::Jump_InDirection(const Jump_InOrder* order, int length) {
	move_type=1;
	jumping = true;
	static int move_stage = 0;
	pm->set_dir(order[move_stage].x, order[move_stage].y);
	move_stage++;
	if (move_stage >= length )
	{
		move_stage = 0;
		move_type = 0;
		jumping = false;

	}

}
void  Mario_abilities::Jump()
{
	static Jump_InOrder currdir;
	if (!jumping)
	{
    currdir.x = pm->GetDirX();
	currdir.y = pm->GetDirY();
	}
	
	if(currdir.x==1 && currdir.y==0)
	Jump_InDirection(jump_inorder_right, move_count_right);

	if (currdir.x == -1 && currdir.y == 0)
		Jump_InDirection(jump_inorder_left, move_count_left);

	if (currdir.x == 0 && currdir.y == 0)
		Jump_InDirection(jump_inorder_neutral, move_count_neutral);
}



int  Mario_abilities::GetMoveType(char key)
{
bool isgrounded=pm->IsColliding(player->collisions, player->col_length, pm->GetX(), pm->GetY() + 1);
if (key == 'w' && isgrounded)
    {
	move_type= 1;
	}
if (key == 'w' && isgrounded&&pm->GetCurrentBackgroundChar()=='H')
{
	ladder_up = true;
	move_type=  2;
}
if (key == 'x' && isgrounded && board->getChar(pm->GetX(),pm->GetY() + 2) == 'H')
{
	ladder_up = false;
	move_type = 2;
}
return move_type;
}


void Mario_abilities::InLadder()
{

	if (ladder_up)
	{
		bool detected_ceiling = pm->IsColliding(player->collisions, player->col_length, pm->GetX(), pm->GetY()-1);
		
		if (detected_ceiling)
		{
			move_type = 0;
			pm->set_dir(0, -2);
			pm->move(player->collisions, player->col_length);
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
        detected_ground  = pm->IsColliding(player->collisions, player->col_length, pm->GetX(), pm->GetY() + 2);
        pm->set_dir(0, 2);
		once = true;
		}
		else
		{
       detected_ground = pm->IsColliding(player->collisions, player->col_length, pm->GetX(), pm->GetY() + 1);
        pm->set_dir(0, 1);
		}
	    
		
		if (detected_ground)
		{
			move_type = 0;
			pm->set_dir(0, 0);
			once = false;
		
		}
	}
}
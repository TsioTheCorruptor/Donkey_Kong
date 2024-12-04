#include "Mario_abilities.h"
void  Mario_abilities::Jump_InDirection(const Jump_InOrder* order, int length) {
	jumping = true;
	static int move_stage = 0;
	pm->set_dir(order[move_stage].x, order[move_stage].y);
	move_stage++;
	if (move_stage >= length )
	{
		move_stage = 0;
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
	
	if(currdir.x==1&&currdir.y==0)
	Jump_InDirection(jump_inorder_right, move_count_right);

	if (currdir.x == -1 && currdir.y == 0)
		Jump_InDirection(jump_inorder_left, move_count_left);

	if (currdir.x == 0 && currdir.y == 0)
		Jump_InDirection(jump_inorder_neutral, move_count_neutral);
}
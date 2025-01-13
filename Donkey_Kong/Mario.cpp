#include "Mario.h"

void  Mario::Jump_InDirection(const Jump_InOrder* order, int length, int currdirx, int currdiry) {
	curr_move=jumping;
	isjumping = true;
	//go through every dir in the order array,advence one index per iteration
	player_movement->set_dir(order[move_stage].x, order[move_stage].y,true);
	move_stage++;
	//stop jumping if end of order reached,or if the player collided with something
	if (move_stage >= length|| player_movement->IsCollidingInNextDir(collisions,col_length)){
		move_stage = 0;
		curr_move=no_moves;
		isjumping = false;
	}
}
void  Mario::Jump() {

	// save dir to set it back after jump
	if (!isjumping){
		savedirX = player_movement->GetDirX();
		savedirY = player_movement->GetDirY();
	}
	//jump according to dir
	if (savedirX == 1 && savedirY == 0)
		Jump_InDirection(jump_inorder_right, move_count_right, savedirX, savedirY);
	if (savedirX == -1 && savedirY == 0)
		Jump_InDirection(jump_inorder_left, move_count_left, savedirX, savedirY);
	if (savedirX == 0 && savedirY == 0)
		Jump_InDirection(jump_inorder_neutral, move_count_neutral, savedirX, savedirY);
}
//get mario state according to key pressed and other info
int  Mario::GetMoveType(char key) {
	key = tolower(key);
	bool isgrounded = player_movement->IsCollidingInGround(collisions, col_length);
	if (key == upkey && isgrounded){
		curr_move=jumping;
	}
	if (key == upkey && isgrounded && player_movement->GetCurrentBackgroundChar() ==ladder_char){
		ladder_up = true;
		curr_move=ladder;
	}
	if (key == downkey && isgrounded && board->getOgChar(player_movement->GetX(), player_movement->GetY() + 2) == 'H'){
		ladder_up = false;
		curr_move=ladder;
	}
	return curr_move;
}
void Mario::InLadder(){
	//if going up the ladder
	//move up until detecting ceiling(collider above the player)
	if (ladder_up){
		bool detected_ceiling = player_movement->IsColliding(collisions, col_length, player_movement->GetX(), player_movement->GetY() - 1);
		if (detected_ceiling){
			curr_move=no_moves;
			//move two points up to get above floor(if possible)
			player_movement->set_dir(0, -2,true);
			player_movement->move(collisions,col_length);
			//stop moving after going up
			player_movement->set_dir(0, 0,false);
		}
		else player_movement->set_dir(0, -1,true);
	}
	//if going down ladder
	if (!ladder_up){
		bool detected_ground = false;
		//go two points down to go below floor
		if (go_below_ground == false){
			detected_ground = player_movement->IsColliding(collisions, col_length, player_movement->GetX(), player_movement->GetY() + 2);
			player_movement->set_dir(0, 2,false);
			go_below_ground = true;
		}
		//after going below ground once,go down until ground
		else {
			detected_ground = player_movement->IsCollidingInGround(collisions, col_length);
			player_movement->set_dir(0, 1,true);
		}

		//if ground is detected,stop going down ladder
		if (detected_ground){
			curr_move=no_moves;
			player_movement->set_dir(0, 0,false);
			go_below_ground = false;
		}
	}
}
void Mario::DoMarioMoves(int key){
	switch (GetMoveType(key)){
	case no_moves://default case
		player_movement->move(GetCollisionArray(), GetCollisionArrayLength());
		std::cout.flush();
		break;
	case jumping:
		Jump();
		player_movement->move(GetCollisionArray(), GetCollisionArrayLength());
		//save direction before jumping
		if (!player_movement->is_dir_0()){
			player_movement->set_dir(GetSavedDirX(),GetSavedDirY(), false);
		}
		break;
	case ladder:
		InLadder();
		player_movement->move(GetCollisionArray(), GetCollisionArrayLength());
		break;
	}
}
//set movement dir according to key pressed
void Mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			player_movement->set_dir(directions[i].x,directions[i].y,false);
			return;
		}
	}
}
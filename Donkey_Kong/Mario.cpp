#include "Mario.h"

void  Mario::Jump_InDirection(const Jump_InOrder* order, int length, int currdirx, int currdiry) {

	curr_move=move_type::jumping;
	isjumping = true;
	//go through every dir in the order array,advence one index per iteration
	player_movement->set_dir(order[move_stage].x, order[move_stage].y,true);
	move_stage++;
	//stop jumping if end of order reached,or if the player collided with something
	if (move_stage >= length|| player_movement->IsCollidingInNextDir(player_abilities->GetCollisionArray(), player_abilities->GetCollisionArrayLength())){
		move_stage = 0;
		curr_move=move_type::no_moves;
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
	bool isgrounded = player_movement->IsCollidingInGround(player_abilities->GetCollisionArray(), player_abilities->GetCollisionArrayLength());
	if (key == upkey && isgrounded){
		curr_move=move_type::jumping;
	}
	if (key == upkey && isgrounded && player_movement->GetCurrentBackgroundChar() ==ladder_char){
		player_abilities->set_ladder_up(true);
		curr_move=move_type::ladder;
	}
	if (key == downkey && isgrounded && board->getOgChar(player_movement->GetX(), player_movement->GetY() + 2) == 'H'){
		player_abilities->set_ladder_up(false);
		curr_move=move_type::ladder;
	}
	return int(curr_move);
}

void Mario::DoMarioMoves(int key){

	if (player_movement->GetCurrentBackgroundChar() == hammer_char) {
		board->setOgChar(player_movement->GetX(), player_movement->GetY(), ' ');
		set_hammer(true);
	}

	switch (GetMoveType(key)){
		case int(move_type::no_moves) ://default case
		player_movement->move(player_abilities->GetCollisionArray(), player_abilities->GetCollisionArrayLength());
		std::cout.flush();
		break;
		case int(move_type::jumping) :
		Jump();
		player_movement->move(player_abilities->GetCollisionArray(), player_abilities->GetCollisionArrayLength());
		//save direction before jumping
		if (!player_movement->is_dir_0()){
			player_movement->set_dir(GetSavedDirX(),GetSavedDirY(), false);
		}
		break;
		case int(move_type::ladder) :
		if (!(player_abilities->InLadder(player_movement))) {
				curr_move = move_type::no_moves;
		}
		player_movement->move(player_abilities->GetCollisionArray(), player_abilities->GetCollisionArrayLength());
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

void Mario::drawHammer() {

	char oGchar = board->getOgChar(player_movement->GetX(), player_movement->GetY() - 1);
	//Draw the hammer only if mario holds one, and if he doesnt touch the ceileing
	if (has_hammer() && player_movement->GetY() != 0) {
		//If the player pressed 'p' AND he is on ground AND he isnt jumping, AND he's moving, only then print the 'p' beside Mario
		//to avoid unnesscery printing
		if (isHitting == true && player_movement->IsGrounded() && isjumping == false && player_movement->GetDirX() != 0) {
			//Draw the original board char above Mario head
			board->draw_InPosition(player_movement->GetX(), player_movement->GetY() - 1, oGchar);
			//Print the hammer beside Mario as long as he didn't reach the edges of the board
			if (player_movement->GetX() != 0 && player_movement->GetX() != 80) {
				board->draw_InPosition(player_movement->GetX() + player_movement->GetDirX(), player_movement->GetY(), hammer_char);
			}
		}
		//If he isnt attacking, just print the hammer above his head
		else {
			board->draw_InPosition(player_movement->GetX(), player_movement->GetY() - 1, hammer_char);
		}
	}
}

void Mario::eraseHammer() {

	char oGchar = board->getOgChar(player_movement->GetX(), player_movement->GetY() - 1);
	char oGchar2 = board->getOgChar(player_movement->GetX(), player_movement->GetY() - 2);
	//Draw the original board char above Mario head, and also 2 chars above Mario head (incase Mario jumped)
	if (has_hammer()) {
		board->draw_InPosition(player_movement->GetX(), player_movement->GetY() - 1, oGchar);
		board->draw_InPosition(player_movement->GetX(), player_movement->GetY() - 2, oGchar2);
		isHitting = false;
	}
}




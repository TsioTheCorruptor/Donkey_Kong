
#include "ClimbingGhost.h"

void ClimbingGhost::checkAndMoveGhost() {

	//If the ghost finds a ladder 'above' it
	if (IsGrounded() && GetCurrentBackgroundChar() == 'H') {
		//Climb up if Mario is above the ghost (and is grounded)
		if (player_movement->IsGrounded() && (GetY() - player_movement->GetY() > 0)) {
			ghost_abilities.set_ladder_up(true);
			setClimbing(true);
			
		}
	}

	//If the ghost finds a ladder below it
	if (IsGrounded() && pBoard->getOgChar(GetX(), GetY() + 2) == 'H') {
		//Climb down if Mario is below the ghost (and is grounded)
		if (player_movement->IsGrounded() && (GetY() - player_movement->GetY() < 0)) {
			ghost_abilities.set_ladder_up(false);
			setClimbing(true);
			
		}
	}

	if (isClimbing()) {
		if (!ghost_abilities.InLadder(this)){
			setClimbing(false);
		}
		move(ghost_abilities.GetCollisionArray(), ghost_abilities.GetCollisionArrayLength());
	}

	else {
		Ghost::checkAndMoveGhost();
	}
}
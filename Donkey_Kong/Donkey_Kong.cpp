// Donkey_Kong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "movement.h"
#include "Mario.h"
#include "gameManager.h"
#include "Mario_abilities.h"
// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario player;
	Mario_abilities ma;
	Pointmovement p;
	bool in_action = false;
	bool test = false;
	player.set_mario_char('@');
	p.set_movement_char(player.get_mario_char());
	//p.setBoard(board);
	p.setBoard(board);
	ma.SetPointMovement(p);
	ma.SetMario(player);
	ma.SetBoard(board);
	while (true) {
		char key = ' ';
		p.draw();
		if (_kbhit()) {
			
			 key = _getch();
			if (key == ESC) break;
			p.keyPressed(key);
		}
		Sleep(80);
		if(!p.is_dir_0())
		p.erase();
		bool isgrounded = p.IsColliding(player.collisions, player.col_length, p.GetX(), p.GetY() + 1);
		bool hit_ceiling = p.IsColliding(player.collisions, player.col_length, p.GetX(), p.GetY() -1);
	
/* if (p.GetCurrentBackgroundChar() == 'H' && key == 'w' && isgrounded || in_action == true)
		{
			p.set_dir(0, -1);
			p.move(player.collisions, player.col_length);
			in_action = true;
			if (hit_ceiling)
				in_action = false;
			continue;
		}   
 else
   if ((isgrounded && key == 'w') || ma.is_jumping())
		{
			 ma.Jump();
		}*/

		switch (ma.GetMoveType(key))
		{
		case 0://default case
		
          p.move(player.collisions, player.col_length);
		  std::cout.flush();
		break;

		case 1:
			ma.Jump();
			p.move(player.collisions, player.col_length);	
	    break;
		case 2:
			ma.InLadder();
			p.move(player.collisions, player.col_length);
			break;
		 }
		
		
		
	}
}



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
	
	player.set_mario_char('@');
	p.set_movement_char(player.get_mario_char());
	//p.setBoard(board);
	p.setBoard(board);
	ma.SetPointMovement(p);
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

if ((isgrounded && key == 'w') || ma.is_jumping())
		{
			ma.Jump();
			
		}
		
		
		p.move(player.collisions,player.col_length);
		
		
	}
}



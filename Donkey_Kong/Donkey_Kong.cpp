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
#include "Barreles.h"
// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario player;
	Pointmovement player_point;
	bool in_action = false;
	bool test = false;
	player.set_mario_char('@');
	player_point.set_movement_char(player.get_mario_char());
	player_point.setBoard(board);
	player.SetPointMovement(player_point);
	player.SetBoard(board);
	const int size = Barrel::getBarrelsAmount();
	Barrel barrel[size];
	Pointmovement barrel_point[size];
	for (int i = 0; i < size; i++) {
		barrel[i].setTheBarrel(barrel[i], barrel_point[i], board, i);
	}
	while (true) {
		char key = ' ';
		player_point.draw();
		for (int i = 0; i < size; i++) {
			barrel[i].checkAndDrawBarrel(barrel[i], barrel_point[i]);
		}
		if (_kbhit()) {
			
			 key = _getch();
			if (key == ESC) break;
			player_point.keyPressed(key);
		}
		Sleep(80);
		if(!player_point.is_dir_0())
			player_point.erase();
		for (int i = 0; i < size; i++) {
			barrel[i].moveBarrel(barrel[i], barrel_point[i]);
		}
		
		switch (player.GetMoveType(key))
		{
		case player.no_moves ://default case
		
			player_point.move(player.collisions, player.col_length);
		  std::cout.flush();
		break;

		case player.jumping:
			player.Jump();
			player_point.move(player.collisions, player.col_length);
	    break;
		case player.ladder:
			player.InLadder();
			player_point.move(player.collisions, player.col_length);
			break;
		 }
	}
}



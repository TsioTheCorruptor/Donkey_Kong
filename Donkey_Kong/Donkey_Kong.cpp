// Donkey_Kong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "gameManager.h"

//constexpr int ESC = 27;

int main() {
	Game game;
	game.level();
	/*ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario player;
	Pointmovement player_point;
	player.set_mario_char('@');
	player_point.set_movement_char(player.get_mario_char());
	player_point.setBoard(board);
	player.SetPointMovement(player_point);
	player.SetBoard(board);
	std::vector <Barrel> barrel;
	std::vector <Pointmovement> barrel_point;
	int waitTime = 10;
	while (true) {

		//Every 10 itteration create a new barrel and connect it to the board
		if (waitTime % 10 == 0) {
			int currIndex = barrel.size();
			barrel.emplace(barrel.begin(), Barrel());
			barrel_point.emplace(barrel_point.begin(), Pointmovement());
			barrel.front().setTheBarrel(barrel.front(), barrel_point.front(), board, 0);
			for (int i = 1; i < barrel.size(); ++i) {
				barrel[i].SetPointMovement(barrel_point[i]);
			}
		}
		char key = ' ';
		player_point.draw();
		for (int i = 0; i < barrel.size(); i++) {
			barrel[i].checkAndDrawBarrel(barrel[i], barrel_point[i]);
		}
		if (_kbhit()) {
			
			 key = _getch();
			if (key == ESC) break;
			player_point.keyPressed(key);
		}
		Sleep(80);
		if (!player_point.is_dir_0())
			player_point.erase();
		for (int i = 0; i < barrel.size(); i++) {
			barrel[i].moveBarrel(barrel[i], barrel_point[i]);
			if (barrel[i].isExploded()) 
				barrel.pop_back();
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

			if(!player_point.is_dir_0())
			player_point.set_dir(player.currdir.x, player.currdir.y);

	    break;
		case player.ladder:
			player.InLadder();
			player_point.move(player.collisions, player.col_length);
			break;
		 }
		waitTime++;
		//std::cout << "reached loop:" << waitTime / 10 << std::endl;
	}*/
}



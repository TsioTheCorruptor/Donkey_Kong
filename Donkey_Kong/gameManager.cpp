#include <cstring>
#include <iostream>

#include "gameManager.h"
void Game::level()
{
ShowConsoleCursor(false);
	
	pBoard.reset();
	pBoard.print();
	Mario player;
	Pointmovement player_point('@',9,3,pBoard);
	player.set_mario_char('@');
	player_point.set_movement_char(player.get_mario_char());
	player.SetPointMovement(player_point);
	player.SetBoard(pBoard);
	std::vector <Barrel> barrel;
	int waitTime = 10;
	while (true) {

		//Every 10 itteration create a new barrel and connect it to the board
		if (waitTime % 15 == 0) {

		//	Pointmovement barrel_point;
			barrel.emplace_back(9, 3, Pointmovement('O', 10, 3, pBoard), pBoard);

		}


	
		char key = ' ';
		
		//pBoard.draw_InPosition(player_point.GetX(), player_point.GetY(), player_point.GetPrevChar());
		//player_point.SetPrevChar();
		player_point.draw();	
		for (auto it = barrel.begin(); it != barrel.end();)
		{
			//it->SetPrevChar();
         it->DrawBarrel();
		 it++;
		}

	

		if (_kbhit()) {

			key = _getch();
			if (key == ESC) break;
			
			player_point.keyPressed(key);
		}

		Sleep(80);
		
	
		if (!player_point.is_dir_0())
			player_point.erase();
		
		switch (player.GetMoveType(key))
		{
		case player.no_moves://default case

			player_point.move(player.collisions, player.col_length);
			std::cout.flush();
			break;

		case player.jumping:
			player.Jump();
			player_point.move(player.collisions, player.col_length);

			if (!player_point.is_dir_0() )
			{
             player_point.set_dir(player.currdir.x, player.currdir.y,false);
			}
				

			break;
		case player.ladder:
			player.InLadder();
			player_point.move(player.collisions, player.col_length);
			break;
		}
//DamageTaken(player_point);

		for (auto it = barrel.begin(); it != barrel.end();) {//put in func
			it->checkAndDrawBarrel();

			if (it->isExploded())
			{
				it = barrel.erase(it);
			}
			else
			{
				it++;
			}
		}
		waitTime++;
		
		//std::cout << "reached loop:" << waitTime / 10 << std::endl;
	}
}

void Game::main_game()
{
	
}
void Game::resetGame() {

	//pBoard = new Board();
	pBoard.reset();

	if (newGame == true) {
		health = MAX_HEALTH;
		newGame = false;
	}
	else {
		health = health - 1;
	}
}

void Game::printGame() {

	pBoard.print();
	//printHealth();
}
void Game:: DamageTaken(Pointmovement player_movement)
{
	int playerX = player_movement.GetX();
	int playerY = player_movement.GetY();
	char chr = pBoard.getChar(playerX, playerY+9);
	for (int i = 0; i < col_length; i++)
	{
		if ( chr== damagecollisions[i])
		{
			currhealth--;
			break;
		}
	}
}


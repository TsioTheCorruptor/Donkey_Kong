#include <cstring>
#include <iostream>

#include "gameManager.h"
void Game::level_1()
{
ShowConsoleCursor(false);
	//each reset,before the game loop
    pBoard.reset();
	pBoard.print();
	PrintLives();
	//set starting point for mario and barrels
	int player_startX = 12;
	int player_startY = 22;
	int barrel_startX = 9;
	int barrel_startY = 3;
	
	Pointmovement player_point(player_char,player_startX,player_startY,pBoard);
	Mario player(player_char,ladder_char,player_point,pBoard);
	std::vector <Barrel> barrel;
	
	//each reset,before the game loop

	while (true) {
		
		//Every "barrel_waitTime" iterations create a new barrel 
		if (curr_barrel_waitTime >=barrel_waitTime  ) {
			barrel.emplace_back( Pointmovement(barrel_char, barrel_startX, barrel_startY, pBoard), pBoard);
			curr_barrel_waitTime = 0;
		}
//in this part of the loop,we print the moving objects according to their positions
	// we also check their interactions with each other
		//it is required to draw the barrels first and then the player.
		
		//for each barrel,draw it
		for (auto it = barrel.begin(); it != barrel.end();)
		{
         it->DrawBarrel();
		 it++;
		}
		//check for fall damage and collision damage with barrels,draw player after checking collisions
		DamageTaken(player_point);
		player_point.draw();	
		FallDamageTaken(player_point);
		//check health,reset accordingly
		if(HealthCheck())
		    break;

		if (IsPaulineReached(player_point))
			break;

	
		
			
	
	char key = ' ';
		//in this part we will check the player input,we will also determine if pausing the game in required
		if (_kbhit()) {

			key = _getch();
			if (key == ESC)
			{
				pBoard.printPause();
				pause_game = true;
			}
			player_point.keyPressed(key);
			PauseGame();
		}
		
		//delay per iteration
		Sleep(80);
		
	
		
		//check according to player input which move mario will do
		switch (player.GetMoveType(key))
		{
		case player.no_moves://default case

			player_point.move(player.GetCollisionArray(), player.GetCollisionArrayLength());
			std::cout.flush();
			break;

		case player.jumping:
			player.Jump();
			player_point.move(player.GetCollisionArray(), player.GetCollisionArrayLength());

			//save direction before jumping
			if (!player_point.is_dir_0() )
			{
             player_point.set_dir(player.GetSavedDirX(), player.GetSavedDirY(), false);
			}
			

			break;
		case player.ladder:
			player.InLadder();
			player_point.move(player.GetCollisionArray(), player.GetCollisionArrayLength());
			break;
		}
		DamageTaken(player_point);
		
          //erase char in last position,do it only while mario is moving to prevent flickering
		if (!player_point.is_dir_0())
			player_point.erase();
		//check explosions and move barrels
		for (auto it = barrel.begin(); it != barrel.end();) {//put in func
			it->checkAndMoveBarrel();
			if (it->isExploding())
			{
				ExplosionDamageTaken(it->GetposX(), it->GetposY(), player_point);
			}
			if (it->isExploded())
			{
				//restore char in the explosion pos,remove barrel from database
					it->checkAndMoveBarrel();
					it = barrel.erase(it);
			}
			else
			{
				it++;
			}
		}
		
		
		curr_barrel_waitTime++;
		
		
	}
}

void Game::main_game()
{
	while (true)
	{
		switch (currstate)
		{
		case level:
			level_1();
			break;

		case reset:
			currstate = level;
			currhealth = health_per_reset;
			 check_collision_dir = false;
			 damage_collision_checkX = 0;
			 damage_collision_checkY = 0;
			break;
		case game_over:
			currstate=menu;
			lives = max_lives;
			pBoard.printGameOver();
			Sleep(GO_screentime);
			break;
		case menu:
			pBoard.printMenu();
			inMenu();
			currhealth = health_per_reset;
			
			break;
		case victory:
			currstate = menu;
			lives = max_lives;
			pBoard.printVictory();
			Sleep(Victory_screentime);
			break;
		case exit_game:
			return;
			break;
		case instructions:
			pBoard.printInstructions();

			break;

        }
		
	}
	
}



void Game:: DamageTaken(Pointmovement player_movement)
{
	//get player coordinates in his current position and in next dir
	int playerX = player_movement.GetX();
	int playerY = player_movement.GetY();
	char playerPoint = pBoard.getChar(playerX, playerY);
	//char playerPoint_withdir = pBoard.getChar(playerX+player_movement.GetDirX(), playerY+player_movement.GetDirY());
	
    
	for (int i = 0; i < col_length; i++)
	{
		//if collision is detected at the exact same point,reduce health	
		if (playerPoint == damagecollisions[i])
		{
		currhealth--;
			break;
		}
		/*else
		if (check_collision_dir)
		{
			char pointafterdir = pBoard.getChar(damage_collision_checkX, damage_collision_checkY);

			if (pointafterdir == damagecollisions[i]||playerPoint==damagecollisions[i])
			{
				currhealth--;
			}
			check_collision_dir = false;
			break;
			
		}
		//in case a collision is detected in next direction,save the current player position,in next iteration 
		//check if collision is detected at that position
       if (playerPoint_withdir == damagecollisions[i]||player_movement.is_dir_0())
		{
			damage_collision_checkX = playerX;
			damage_collision_checkY = playerY;
			check_collision_dir = true;
			break;
		}
		*/
	}

	
}
void Game::FallDamageTaken(Pointmovement player_movement)
{
	if (player_movement.GetAirTime() >= falldamage_height && player_movement.IsGrounded())
	{
		currhealth--;
		return;
	}
}
void Game::PauseGame()
{
	char key;
	while (pause_game == true)
	{

		if (_kbhit())
		{

			key = _getch();
			if (key == ESC)
			{
				pBoard.print();
				pause_game = false;

			}

		}
	}
}
   bool Game::HealthCheck()
{
	if (currhealth <= 0)
		{
		lives--;
		if (lives >= 0)
		{
        currstate = reset;
		return true;
		}	
		}
	if(lives<=0)
		{
			currstate = game_over;
			return true;
		}     
	return false;
}
   void Game::inMenu()
   {
	   bool inmenu = true;
	   char key = ' ';
	   printed_instructions = false;
	   while (inmenu==true)
	   {
		   if (_kbhit())
		   {
			   key = _getch();
			   if (key == '1')
			   {
				   inmenu = false;
				   currstate = reset;
			   }
			   if (key == '9')
			   {
				   inmenu = false;
				   currstate = exit_game;
			   }
			   if (key == '8')
			   {
				   if (!printed_instructions)
				    pBoard.printInstructions();
				   printed_instructions = true;
				  
			   }


		   }
	   }
   }
   void Game::ExplosionDamageTaken(int barrelx,int barrely, Pointmovement player_movement)
   {
	   int playerx = player_movement.GetX();
	   int playerY = player_movement.GetY();
	   int dist_Y = abs(playerY - barrely);
	   int dist_X = abs(playerx - barrelx);
	   if (dist_Y <= explosion_damage_radius && dist_X <= explosion_damage_radius)
	   {
		   currhealth--;
		   return;
		   
	   }
   }
   bool Game::IsPaulineReached(Pointmovement player_movement)
   {
	   int playerX = player_movement.GetX();
	   int playerY = player_movement.GetY();
	   char currchar = player_movement.GetCurrentBackgroundChar();
	   if (currchar == pauline_char)
	   {
		   currstate = victory;
		   return true;
	   }
	   return false;
   }
   void Game::PrintLives()
   {
	   gotoxy(health_displayX, health_displayY);
	   std::cout << lives;
   }


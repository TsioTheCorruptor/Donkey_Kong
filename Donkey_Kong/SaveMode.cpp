#include "SaveMode.h"

  /*void SaveMode::level()
{ 
	 
	  

	  // we regenerate the seed for each screen so we can save it as part of the screen steps
	  seedSrand();
	  
	
	
	 ShowConsoleCursor(false);
	 Pointmovement player_point(PlayableChars[int(PlayableChar::player_char)], playerStart.x, playerStart.y, pBoard);
	 ResetLevel(player_point);
	 player_point.set_dir(0, 0, false);
	 Abilities player_abilities(true, false);
	 Mario player(PlayableChars[int(PlayableChar::player_char)], PlayableChars[int(PlayableChar::ladder_char)], player_point, pBoard, player_abilities);

	 

	 while (true) {
		 printTimeScore();
		
		 //Every "barrel_waitTime" iterations create a new barrel 
		 if (curr_barrel_waitTime >= barrel_waitTime && PCharsAmount[int(PlayableChar::dk_char)] != 0) {
			 barrel.emplace_back(Barrel(PlayableChars[int(PlayableChar::barrel_char)], barrelStart.x, barrelStart.y, pBoard, PlayableChars[int(PlayableChar::player_char)]));
			 curr_barrel_waitTime = 0;
		 }
		 //in this part of the loop,we print the moving objects according to their positions
		 //we also check their interactions with each other
		 //it is required to draw the barrels first and then the player.

		 //for each barrel,draw it
		 for (auto it = barrel.begin(); it != barrel.end();) {
			 it->draw();
			 it++;
		 }
		 //for each ghost,draw it
		 for (auto it = ghost.begin(); it != ghost.end();) {
			 (*it)->draw();
			 it++;
		 }
		 //check for fall damage and collision damage with barrels,draw player after checking collisions
		 
		 DamageTaken(player_point);
		 player_point.draw();
		 FallDamageTaken(player_point);
		 //check health,reset accordingly
		 if (HealthCheck()) 
			 break;
		 if (IsPaulineReached(player_point))
			 break;
		 char key = ' ';
		 //in this part we will check the player input,we will also determine if pausing the game in required
		 getPlayerInput(key);
		 //Only activate when Mario is on floor
			  if (player_point.IsGrounded() && (key == PlayableChars[int(PlayableChar::hammer_char)] || key == 'P')) {
				 player.set_hitting(true);
				 usedHammer = true;
			 }
			 else {
				 player.keyPressed(key);
			 }
		 //Draw the hammer above Mario (if he has it) or beside him (if he attacks)
		 player.drawHammer();
		 //delay per iteration(may be specific per level)
		 Sleep(iterationTime);
		 //Check all ghosts and barrels if colided with the hammer
		 if (usedHammer == true) {
			 checkAllGhostsIfHit(player_point);
			 checkAllBarrelsIfHit(player_point);
			 usedHammer = false;
		 }
		 //Erase the hammer after the sleep
		 player.eraseHammer();
		 //check according to player input which move mario will do
		 player.DoMarioMoves(key);
		 //check collisions with barrels again
		 DamageTaken(player_point);
		 //check ghosts coliding
		 checkGhostsColliding();
		 //erase char in last position,do it only while mario is moving to prevent flickering
		 if (!player_point.is_dir_0())
			 player_point.erase();
		 //check explosions and move barrels
		 MoveBarrels(player_point);
		 //move the ghosts
		 MoveGhosts();
		 curr_barrel_waitTime++;
		 
	 } 
}*/
std::string SaveMode:: getStepsFileName() {
	std::string filename_prefix = boardfileNames[currLevel].substr(0, boardfileNames[currLevel].find_last_of('.'));
	std::string stepsFileName = filename_prefix + ".steps";
	return stepsFileName;
}
std::string SaveMode::getResultFileName() {
	std::string filename_prefix = boardfileNames[currLevel].substr(0, boardfileNames[currLevel].find_last_of('.'));
	std::string stepsFileName = filename_prefix + ".results";
	return stepsFileName;
}
 void SaveMode::main_game() {
	 getAllBoardFileNames(boardfileNames);
	 setRandomSeed();
	 
	 while (true) {
		 switch (int(currstate)) {
			 case int(gameState::level) :
				
				 level();
				 break;
				 case int(gameState::level_select) :
					 LevelSelect();
					 seedSrand();
					 break;
					 case int(gameState::get_levelInput) :
						 getLevelInput();
						 break;
						 case int(gameState::manage_errors) :
							 pBoard.printEmpty();
							 printErrors();
							 break;
							 case int(gameState::reset) :
								// inputToSave.push_back(inputInfo(iterationCount + 1, 'r'));
								 currstate = gameState::level;
								 currhealth = health_per_reset;

								 break;
								 case int(gameState::game_over) :
									 
									 currstate = gameState::menu;
									 lives = max_lives;
									 pBoard.printGameOver();
									 Sleep(GO_screentime);
									 saveData();

									 break;
									 case int(gameState::menu) :
										 pBoard.printMenu();
										 inMenu();
										 currhealth = health_per_reset;
										 break;
										 case int(gameState::victory) :
											 resultToSave.push_back(inputInfo(iterationCount-1,'W'));
											 saveData();
											 if (currLevel >= fileamount - 1) {
												 currstate = gameState::menu;
												 lives = max_lives;
												 pBoard.printVictory();
												 Sleep(Victory_screentime);
											 }
											 else {
												 currLevel++;
												 currstate = gameState::level_select;
											 }
										 break;
										 case int(gameState::exit_game) :
											 return;
											 break;
											 case int(gameState::instructions) :
												 pBoard.printInstructions();
												 break;
												 case int(gameState::requestNextLevel) :
													 if (!requestNextLevel())
														 currstate = gameState::exit_game;
													 break;
		 }
	 }
}
 void SaveMode::saveData()
 {
	 std::ofstream result_file(getResultFileName());
	 std::ofstream steps_file(getStepsFileName());
	 int resultsize = resultToSave.size();
	 if (!steps_file.is_open()||!result_file.is_open())
	 {
		 currError = errorType::general;
		 currstate = gameState::manage_errors;
		 return;
	 }
	 result_file << resultToSave.size()<<'\n';
	 for (const auto& input : resultToSave)
	 {
		 result_file << input.iteration << ' ' << input.input << '\n';

	 }
	 result_file << GameTime;
	 steps_file << randomseed << '\n' << int(inputToSave.size());

	 for (const auto& input : inputToSave) {
		 steps_file << '\n' << input.iteration << ' ' << input.input;
	 }
	 steps_file.close();
	 result_file.close();
	 inputToSave.clear();
	 resultToSave.clear();
	 iterationCount = 0;
	 setRandomSeed();

 }
 void SaveMode::getPlayerInput(char& key)
 {
	 if (_kbhit()) {

		 key = _getch();
		 inputToSave.push_back(inputInfo(iterationCount, key));
		 if (key == ESC) {
			 pBoard.printPause();
			 pause_game = true;
		 }

		 PauseGame();
	 }
	 iterationCount++;
 }
 bool SaveMode:: HealthCheck()
 {
	 if (currhealth <= 0) {
		 lives--;
		 if (lives >= 0) {
			 currstate = gameState::reset;
			 resultToSave.push_back(inputInfo(iterationCount,'L'));
			 return true;
		 }
	 }
	 if (lives <= 0) {
		 currstate = gameState::game_over;
		 return true;
	 }
	 return false;
 }
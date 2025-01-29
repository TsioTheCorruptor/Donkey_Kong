#include "LoadMode.h"

/*void LoadMode::level()
{////////////
	seedSrand();
	
	
	////////
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
		//////////
		getPlayerInput(key);
		////////////	
			
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
std::string LoadMode::getStepsFileName() {
	std::string filename_prefix = boardfileNames[currLevel].substr(0, boardfileNames[currLevel].find_last_of('.'));
	std::string stepsFileName = filename_prefix + ".steps";
	return stepsFileName;
}
std::string LoadMode::getResultFileName() {
	std::string filename_prefix = boardfileNames[currLevel].substr(0, boardfileNames[currLevel].find_last_of('.'));
	std::string stepsFileName = filename_prefix + ".results";
	return stepsFileName;
}
void LoadMode::main_game() {
	getAllBoardFileNames(boardfileNames);
	currstate = gameState::level_select;
	iterationTime /= 2;
	 
	
	while (true) {
		switch (int(currstate)) {
			case int(gameState::level) :
				level();
				break;
				case int(gameState::level_select) :
					LevelSelect();
					setupLoad();
					seedSrand();
					break;
						break;
						case int(gameState::manage_errors) :
							pBoard.printEmpty();
							printErrors();
							break;
							case int(gameState::reset) :
								currstate = gameState::level;
								currhealth = health_per_reset;
								break;
								case int(gameState::game_over) :
									if (currScoreToCheck==GameTime)
									{
                                    currstate = gameState::exit_game;
									
									pBoard.printGameOver();
									Sleep(GO_screentime);
									}
									else {
										currstate = gameState::manage_errors;
										currError = errorType::stepMismatch;
									}
									break;
									
										break;
										case int(gameState::victory) :
											
											if (currScoreToCheck == GameTime)
											{
												if (currLevel >= fileamount - 1) {
													currstate = gameState::exit_game;

													pBoard.printVictory();
													Sleep(Victory_screentime);
												}
												else {
													currLevel++;
													currstate = gameState::level_select;
												}
											}
											else {
												currstate = gameState::manage_errors;
												currError = errorType::stepMismatch;
											}

											
											
											break;
											case int(gameState::exit_game) :
												if (isLoad)
													std::cout << "succes running in silent mode!files are valid";
												return;
												break;
												
													case int(gameState::requestNextLevel) :
														if (!requestNextLevel())
															currstate = gameState::exit_game;
														break;
		}
	}

	
}
bool LoadMode:: setupLoad()
{
	resultsize = 0;
	inputcount = 0;
	iterationCount = 0;
	inputToSave.clear();
	resultToCheck.clear();
	std::ifstream steps_file(getStepsFileName());
	std::ifstream result_file(getResultFileName());
	stageResetCount=0;
	
	
	
	if (!steps_file.is_open()||!result_file.is_open()||
		steps_file.peek()==std::ifstream::traits_type::eof()|| result_file.peek() == std::ifstream::traits_type::eof() )
	{
		currstate = gameState::manage_errors;
		currError = errorType::LoadMode;
		return false;
	}

	
	// we regenerate the seed for each screen so we can save it as part of the screen steps
	result_file >> resultsize;
	
	for (int i = 0; i < resultsize; i++)
	{
		int iteration=0;
		char input=' ';
		result_file >> iteration >> input;
		resultToCheck.push_back(inputInfo(iteration, input));
		
	}
	
		
	result_file >> currScoreToCheck;
	steps_file >> randomseed >> stepsize;
	if(resultsize>0)
	maxiteration = resultToCheck[resultsize - 1].iteration;

	for (int i = 0; i < stepsize; i++)
	{
		int iteration=0;
		char input=' ';
		steps_file >> iteration >> input;
		inputToSave.push_back(inputInfo(iteration, input));
		
	}
	steps_file.close();
	result_file.close();
	return true;
}
void LoadMode::printErrors()
{
	gotoxy(0, 0);
	switch (int(currError)) {//print game errors acoording to error state
		case int(errorType::not_found) :
			std::cout << "error loading level!";
			currstate = gameState::manage_errors;
			currError = errorType::LoadMode;
			Sleep(Error_screentime);
			break;
			case int(errorType::bad_board) :
				std::cout << "necessary level elements missing!";
				currstate = gameState::manage_errors;
				currError = errorType::LoadMode;
				Sleep(Error_screentime);
				break;
				case int(errorType::general) :
					std::cout << "error!";
					currstate = gameState::manage_errors;
					currError = errorType::LoadMode;
					Sleep(Error_screentime);
					break;
					case int(errorType::LoadMode) :
						std::cout << "error while playing level in load mode!";
						currstate = gameState::requestNextLevel;
						Sleep(Error_screentime);
						break;
						case int(errorType::stepMismatch) :
							std::cout << "the results do not match correctly to the saved game!";
							currstate = gameState::exit_game;
							Sleep(Error_screentime);
							break;
	}
}
void LoadMode::getPlayerInput(char& key)
{
	if (iterationCount == 193)
		int i = 0;
	if (inputToSave[inputcount].iteration == iterationCount && inputcount < stepsize)
	{

		key = inputToSave[inputcount].input;
		if (inputcount < stepsize - 1)
			inputcount++;

	}
	iterationCount++;
}

bool LoadMode::HealthCheck()
{
	
		if (currhealth <= 0) {
			if (checkDeathResult() == true)
				return true;
		lives--;
		if (lives > 0) {
			currstate = gameState::reset;
			//resultToCheck.push_back(iterationCount);
			return true;
		}
	}
	if (lives <= 0) {
		currstate = gameState::game_over;
		return true;
	}
	return false;

	
	
}
bool LoadMode::checkDeathResult()
{
	
	bool stop = false;
	if (stageResetCount < resultsize)
	{
		if (lives == 1)
			int i = 0;
		if (resultToCheck[stageResetCount].iteration != iterationCount || resultToCheck[stageResetCount].input != 'L')
		{
			stop= true;
		}
		else
		stop= false;

	}
	else stop =true;

	if (stop == true)
	{
		currstate = gameState::manage_errors;
		currError = errorType::stepMismatch;
		
	}
	
stageResetCount++;
	return stop;

	
	
}
bool LoadMode::stopGameLoop()
{
	if (iterationCount-1 > resultToCheck[stageResetCount].iteration)
	{
		
		return true;
		
	}
		
	return false;
}
void LoadMode::doAfterLoop()
{
	/*
	if (maxiteration != iterationCount)
	{
		currstate = gameState::manage_errors;
		currError = errorType::stepMismatch;

	}*/
}
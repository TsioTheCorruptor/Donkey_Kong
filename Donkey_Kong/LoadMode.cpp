#include "LoadMode.h"


std::string LoadMode::getStepsFileName()const {
	std::string filename_prefix = boardfileNames[currLevel].substr(0, boardfileNames[currLevel].find_last_of('.'));
	std::string stepsFileName = filename_prefix + ".steps";
	return stepsFileName;
}
std::string LoadMode::getResultFileName()const {
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
										SilentSucces();
											
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
													
													SilentSucces();
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
	//we will get all input from files ,and fill up the appropriate vector
	resultsize = 0;
	inputcount = 0;
	iterationCount = 0;
	inputToSave.clear();
	resultToCheck.clear();
	std::ifstream steps_file(getStepsFileName());
	std::ifstream result_file(getResultFileName());
	stageResetCount=0;
	//stop if file is empty or file not found
	if (!steps_file.is_open() || !result_file.is_open() ||
		steps_file.peek() == std::ifstream::traits_type::eof() || result_file.peek() == std::ifstream::traits_type::eof())
	{
		currstate = gameState::manage_errors;
		currError = errorType::LoadMode;
		return false;
	}
	result_file >> resultsize;
	//get death/win iteration results
	for (int i = 0; i < resultsize; i++)
	{
		int iteration=0;
		char input=' ';
		result_file >> iteration >> input;
		resultToCheck.push_back(inputInfo(iteration, input));
		
	}
	//get score
	result_file >> currScoreToCheck;
	steps_file >> randomseed >> stepsize;
	if(resultsize>0)
	maxiteration = resultToCheck[resultsize - 1].iteration;
	//get step inputs
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
	switch (int(currError)) {
		//print game errors acoording to error state
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
	//we get input from file if iteration matches
	if(stepsize>0)
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
	//we will check if result matches with results file
		if (currhealth <= 0) {
			if (checkDeathResult() == true)
				return true;
		lives--;
		if (lives > 0) {
			currstate = gameState::reset;
			
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
	//check death  according to results file,if results do not match return error
	bool stop = false;
	if (stageResetCount < resultsize)
	{
		
		if (resultToCheck[stageResetCount].iteration != iterationCount || resultToCheck[stageResetCount].input != LoseChar)
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
	//if iterations dont match stop game loop
	if(resultsize>0)
	if (iterationCount-1 > resultToCheck[stageResetCount].iteration)
	{
		
		return true;
		
	}
		
	return false;
}
void LoadMode::SilentSucces()
{
	if (isSilent)
	{
		pBoard.printEmpty();
		gotoxy(0, 0);
		std::cout << "succes running in silent mode!files are valid";
	}
}

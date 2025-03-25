#include "SaveMode.h"

  
std::string SaveMode:: getStepsFileName()const {
	std::string filename_prefix = boardfileNames[currLevel].substr(0, boardfileNames[currLevel].find_last_of('.'));
	std::string stepsFileName = filename_prefix + ".steps";
	return stepsFileName;
}
std::string SaveMode::getResultFileName()const {
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
						 makeEmptyFiles();

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
											 resultToSave.push_back(inputInfo(iterationCount-1,WinChar));
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
	 //enter saved data into steps an result files
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
		 //save player input
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
			 //save player death
			 resultToSave.push_back(inputInfo(iterationCount,LoseChar));
			 return true;
		 }
	 }
	 if (lives <= 0) {
		 currstate = gameState::game_over;
		 return true;
	 }
	 return false;
 }
 void SaveMode::makeEmptyFiles()const
 {
	 // 1) Iterate over all files in the current directory
	 namespace fs = std::filesystem;
	 for (const auto& entry : fs::directory_iterator(fs::current_path()))
	 {
		 // 2) Check if the filename ends with .steps or .result
		 auto path = entry.path();
		 auto filenameStr = path.filename().string();

		 // A simple approach to detect the endings:
		 if (filenameStr.size() >= 6) // enough length for ".steps" or ".result"
		 {
			 // Check for ".steps" or ".result"
			 if (filenameStr.substr(0, 5) == "dkong" && (path.extension() == ".steps" || (path.extension() == ".results")))

			 {
				 // 3) Truncate the file to empty it
				 std::ofstream file(path, std::ios::out | std::ios::trunc);
				 if (!file.is_open())
				 {
					 std::cerr << "Warning: Failed to truncate " << filenameStr << std::endl;
					 Sleep(1000);
				 }
				 
			 }
		 }
	 }
 }
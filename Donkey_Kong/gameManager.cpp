

#include "gameManager.h"
void Game::level_1() {
	
	ShowConsoleCursor(false);
	Pointmovement player_point(PlayableChars[int(PlayableChar::player_char)],playerStart.x,playerStart.y,pBoard);
	player_point.set_dir(0, 0,false);
	Mario player(PlayableChars[int(PlayableChar::player_char)], PlayableChars[int(PlayableChar::ladder_char)],player_point,pBoard);

	//each reset,before the game loop

	while (true) {
		printTimeScore();

		//Every "barrel_waitTime" iterations create a new barrel 
		if (curr_barrel_waitTime >=barrel_waitTime&&PCharsAmount[int(PlayableChar::dk_char)]!=0) {
			barrel.emplace_back( Barrel(PlayableChars[int(PlayableChar::barrel_char)],barrelStart.x, barrelStart.y, pBoard));
			curr_barrel_waitTime = 0;
		}
		//in this part of the loop,we print the moving objects according to their positions
		//we also check their interactions with each other
		//it is required to draw the barrels first and then the player.
		
		//for each barrel,draw it
		for (auto it = barrel.begin(); it != barrel.end();){
			it->draw();
			it++;
		}
		//for each ghost,draw it
		for (auto it = ghost.begin(); it != ghost.end();) {
			it->draw();
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
			if (key == ESC){
				pBoard.printPause();
				pause_game = true;
			}
			player.keyPressed(key);
			PauseGame();
		}
		//delay per iteration(may be specific per level)
		Sleep(iterationTime);
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
}
//the entire game loop
void Game::main_game(){

	getAllBoardFileNames(boardfileNames);
	std::srand(unsigned int(time(0)));
	while (true){
		switch (int(currstate)){
			case int(gameState::level) :
				level_1();
				break;
			case int(gameState::level_select) :	
				LevelSelect();
				break;
				case int(gameState::get_levelInput) :
					getLevelInput();
					break;
			case int(gameState::manage_errors) :
				pBoard.printEmpty();
				printErrors();
				break;
			case int(gameState::reset) :
				currstate = gameState::level;
				currhealth = health_per_reset;
				ResetLevel();
				break;
			case int(gameState::game_over) :
				currstate = gameState::menu;
				lives = max_lives;
				pBoard.printGameOver();
				Sleep(GO_screentime);
				break;
			case int(gameState::menu) :
				pBoard.printMenu();
				inMenu();
				currhealth = health_per_reset;
				break;
			case int(gameState::victory) :
				if (currLevel >= fileamount-1) {
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
		}
	}
}
void Game::DamageTaken(Pointmovement player_movement){
	//get player coordinates in his current position and in next dir
	int playerX = player_movement.GetX();
	int playerY = player_movement.GetY();
	char playerPoint = pBoard.getChar(playerX, playerY);
	
	for (int i = 0; i < col_length; i++){
		//if collision is detected at the exact same point,reduce health	
		if (playerPoint == damagecollisions[i]){
			currhealth--;
			break;
		}
	}
}
void Game::FallDamageTaken(Pointmovement player_movement){
	if (player_movement.GetAirTime() >= falldamage_height && player_movement.IsGrounded()){
		currhealth--;
		return;
	}
}
void Game::PauseGame(){
	char key;
	while (pause_game == true)
//be in this while loop until player wants to exit pause,when exiting pause continues the game normally
	{

		if (_kbhit())
		{

			key = _getch();
			if (key == ESC)
			{
				pBoard.print();
				PrintLives();
				pause_game = false;
				std::cout.flush();

			}

		}
	}
}
//if health got reduced to 0 or lives got reduced to 0,change the game state accordingly,return true to exit level loop
bool Game::HealthCheck(){
	
	if (currhealth <= 0){
		lives--;
		if (lives >= 0){
			currstate = gameState::reset;
			return true;
		}	
	}
	if(lives<=0){
		currstate = gameState::game_over;
		return true;
	}     
	return false;
}
void Game::inMenu() {
	bool inmenu = true;
	char key = ' ';
	GameTime = 0;
	printed_instructions = false;

	while (inmenu==true){
		//the menu options
		if (_kbhit()){
			key = _getch();
			if (key == '1'){
				inmenu = false;
				//switchedLevelSelect = false;
				//getLevelInput();
				//if(!switchedLevelSelect)
				currstate = gameState::get_levelInput;
			}
			if (key == '9'){
				inmenu = false;
				currstate = gameState::exit_game;
			}
			if (key == '8'){
				//print instructions only once per menu entry if required
				if (!printed_instructions)
				pBoard.printInstructions();
				printed_instructions = true; 
			}
		}
	}
}
//check distance between explosion and player,reduce health if player is in radius of explosion
void Game::ExplosionDamageTaken(int barrelx,int barrely, Pointmovement player_movement){
	int playerx = player_movement.GetX();
	int playerY = player_movement.GetY();
	int dist_Y = abs(playerY - barrely);
	int dist_X = abs(playerx - barrelx);
	if (dist_Y <= explosion_damage_radius && dist_X <= explosion_damage_radius){
		currhealth--;
		return;
	}
}
//check if olayer won the game(reached pauline),in that case return true to stop level loop
bool Game::IsPaulineReached(Pointmovement player_movement){

	int playerX = player_movement.GetX();
	int playerY = player_movement.GetY();
	char currchar = player_movement.GetCurrentBackgroundChar();
	if (currchar == PlayableChars[int(PlayableChar::pauline_char)]){
		currstate = gameState::victory;
		return true;
	}
	return false;
}
void Game::PrintLives() const{
	gotoxy(health_displayX, health_displayY);
	std::cout << lives;
}
void Game::ResetLevel(){

	
	barrel.clear();
	
	resetGhosts();
	pBoard.reset();
	pBoard.print();
	printGameInfo();
	
}
void Game::MoveBarrels(Pointmovement player_movement){
	for (auto it = barrel.begin(); it != barrel.end();) {
		it->checkAndMoveBarrel();
		if (it->isExploding()){
			ExplosionDamageTaken(it->GetX(), it->GetY(),player_movement);
		}
		if (it->isExploded()){
			//restore char in the explosion pos,remove barrel from database
			it->checkAndMoveBarrel();
			it = barrel.erase(it);
		}
		else {
			//go to next barrel
			it++;
		}
	}
}
void Game::checkGhostsColliding() {
	
	for (int i = 0; i < ghost.size(); ++i) {
		ghost[i].ghostCollision();
	}
}
void Game::MoveGhosts() {
  
	for (int i = 0; i < ghost.size(); ++i) {
		ghost[i].checkAndMoveGhost();
	}
}
void Game::getAllBoardFileNames(std::vector<std::string>&vec_to_fill) {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 5) == "dkong" && filename.extension() == ".screen") {
			std::cout << " ^ added!!\n";
			vec_to_fill.push_back(filenameStr);
		}
	}
	if (vec_to_fill.empty()) {
		std::cout << "No matching board files found in the current directory." << std::endl;
	}
	fileamount = boardfileNames.size();
}
bool Game::getBoardData() {

	memset(PCharsAmount, 0, sizeof(PCharsAmount));
	StartCoord currcoord;
	char chr = ' ';
	
	//chnge magic numbers
	for (int row = 0; row < 25; row++){
		for (int col = 0; col < 80; col++){
			currcoord = { col,row };
			chr = pBoard.getOgChar(col,row );
			switch (chr){
			case PlayableChars[ int(PlayableChar::player_char)] :
				if (PCharsAmount[int(PlayableChar::player_char)] < 1)
					playerStart = currcoord;
				pBoard.setChar(col,row , ' '); 
				pBoard.setOgChar(col,row , ' '); 
				PCharsAmount[int(PlayableChar::player_char)]++;
				break;
			case PlayableChars[int(PlayableChar::dk_char)]:
				if (PCharsAmount[int(PlayableChar::dk_char)] < 1)
					barrelStart = currcoord;
				else{
					pBoard.setChar(col,row , ' ');
					pBoard.setOgChar(col,row , ' ');
				}	
                PCharsAmount[int(PlayableChar::dk_char)]++;
				break;
			case PlayableChars[int(PlayableChar::ghost_char)]:
				PCharsAmount[int(PlayableChar::ghost_char)]++;
				//ghost.emplace_back(Ghost(PlayableChars[int(PlayableChar::ghost_char)], col, row, pBoard, pBoard));
				ghostStart.emplace_back(currcoord);
				pBoard.setChar(col, row, ' ');
				pBoard.setOgChar(col, row, ' ');
				break;
			case PlayableChars[int(PlayableChar::pauline_char)]:
				if (PCharsAmount[int(PlayableChar::pauline_char)] < 1)
					paulineCoord = currcoord;
				else {
					pBoard.setChar(col, row, ' ');
					pBoard.setOgChar(col, row, ' ');

				}
				PCharsAmount[int(PlayableChar::pauline_char)]++;
				break;
			case PlayableChars[int(PlayableChar::legend_char)]:
				
				if (PCharsAmount[int(PlayableChar::legend_char)] < 1) {
				legendCoord = currcoord;
				pBoard.setChar(col, row, ' ');
				pBoard.setOgChar(col, row, ' ');
				}
				PCharsAmount[int(PlayableChar::legend_char)]++;
				break;
			}
		}
	}
	if (PCharsAmount[int(PlayableChar::player_char)] == 0 || PCharsAmount[int(PlayableChar::pauline_char)] == 0|| PCharsAmount[int(PlayableChar::legend_char)] == 0)
		return false;
	return true;
 }
void Game::printErrors() {
	gotoxy(0, 0);
	switch (int(currError)){
		case int(errorType::not_found) :
			std::cout << "error loading level!,returning to menu";
			currstate = gameState::menu;
			Sleep(2000);
			break;
		case int(errorType::bad_board) :
			std::cout << "necessary level elements missing!,returning to menu";
			currstate = gameState::menu;
			Sleep(2000);
			break;
		case int(errorType::general) :
			std::cout << "error!,returning to menu";
			currstate = gameState::menu;
			Sleep(2000);
			break;
	}
}  
void Game::resetGhosts(){

	ghost.clear();
	int k = PCharsAmount[int(PlayableChar::ghost_char)];
	for (int i =0 ;i<PCharsAmount[int(PlayableChar::ghost_char)];i++){
		StartCoord ghostPos = ghostStart[i];
		ghost.emplace_back(Ghost(PlayableChars[int(PlayableChar::ghost_char)], ghostPos.x, ghostPos.y, pBoard));
	}
}
void Game::getLevelInput(){
	StartCoord printInputText = { 33,18 };
	int maxfiles = 30;
	int currinputIndex = 0;
	char inputDisplay[3] = "XX";
	char resetinputDisplay[3] = "XX";

	pBoard.printEmpty();
	gotoxy(printInputText.x, printInputText.y);
	std::cout << "Enter Level Input";
	printLevelInput(inputDisplay);
	gotoxy(0, 0);
	
	
	int resetdelay = 200;
	
	fileamount = boardfileNames.size();
	if (fileamount > 0&&fileamount<maxfiles) {
		printFileNames();	
		while (true){
			if (_kbhit()){
				char key = _getch();
				if (key == 'D') {
					currstate = gameState::get_levelInput;
					
					return;
				}
				if (key - '0'+1 >= 1 && key - '0' <= fileamount) {
					//currLevel = key - '0'-1;
					inputDisplay[currinputIndex] = key;
					printLevelInput(inputDisplay);
					currinputIndex++;
					if (currinputIndex == 2) {
						currinputIndex = 0;
						if (checkLevelInput(inputDisplay, fileamount))
							break;
                        #pragma warning(suppress : 4996) // to allow strcpy
						strcpy(inputDisplay, resetinputDisplay);
						Sleep(resetdelay);
						printLevelInput(inputDisplay);

					}
						
					//break;
				}
			}
		}
	}
	else {
		if(fileamount<=0)
		std::cout << "no levels found!";
		else if(fileamount>maxfiles)
		std::cout << "too many levels!";

		Sleep(Error_screentime);
	} 
}
void Game::LevelSelect() {

	if (fileamount > 0) {
		if (!pBoard.load(boardfileNames[currLevel])) {
			currError = errorType::not_found;
			currstate = gameState::manage_errors;
		}
		else {
			if (!getBoardData()) {
				currError = errorType::bad_board;
				currstate = gameState::manage_errors;
			}
			else
				currstate = gameState::reset;
		}
	}
	else {
		currstate = gameState::menu;
	}
}
void Game:: printLevelInput(char inputstr[])const {
	StartCoord printcoord = { 40,20 };
	
	gotoxy(printcoord.x, printcoord.y);
	std::cout << inputstr;

}
bool Game::checkLevelInput(char input[], int fileamount){
	int inputnum = atoi(input);
	if (inputnum <= fileamount-1 && inputnum >= 0)
	{
		currstate = gameState::level_select;
		currLevel = inputnum;
		return true;
	}
	return false;
}
void Game::printFileNames() {
	int printcount = 0;
	const char pressXstr[] = "  ->press";
	int filelength = strlen(boardfileNames[0].c_str());
	int pressXstrlength = strlen(pressXstr);
	
	
		for (int i = 0; i < fileamount; i++) {
			if (printcount == 11) {
				printcount = 0;
				gotoxy(filelength + pressXstrlength + 3, 0);
			}
			std::cout << boardfileNames[i] << pressXstr << int(i / 10) << i % 10 << '\n';
			printcount++;
		}
	
}
void Game::printGameInfo() const
{
	gotoxy(legendCoord.x, legendCoord.y);
	std::cout << "Health: " <<lives;
	gotoxy(legendCoord.x, legendCoord.y+1);
	std::cout << "Level: " << currLevel;
	gotoxy(legendCoord.x, legendCoord.y + 2);
	std::cout << "Time: " << GameTime;
}
void Game::printTimeScore() {
	iterationCount++;
	if (iterationCount >= iterationUntilSec) {
		GameTime++;
		gotoxy(legendCoord.x, legendCoord.y + 2);
		std::cout << "Time: " << GameTime;
		iterationCount = 0;
	}


}


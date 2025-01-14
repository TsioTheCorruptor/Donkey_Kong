#pragma once
#include "Board.h"
#include "utils.h"
#include "movement.h"
#include "Mario.h"
#include "Barreles.h"
#include "Ghost.h"
#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <time.h>

class Game {
	//const chars
	struct StartCoord { int x=10, y=22; }; // inner private struct
	static constexpr int PcharCount = 8;
	static constexpr char PlayableChars[] = { '@','$','&','H','O','x','L','p'};
	enum class PlayableChar { player_char, pauline_char,dk_char, ladder_char, barrel_char, ghost_char,legend_char, hammer_char };
	StartCoord playerStart,barrelStart,paulineCoord,legendCoord,hammerCoord;
	std::vector <StartCoord> ghostStart;
	char PCharsAmount[PcharCount] = {};
	
	const char enterGame = '1';
	const char viewInstructions = '8';
	const char exitGame = '9';
	static constexpr int ESC = 27;
	//game parameters
	const int rowMax = 25;
	const int colMax = 80;
	int maxFilesPerScreen = 7;
	int levelSelectScreenIndex = 0;
	const int iterationTime = 80;
	const int iterationUntilSec = (1000 / iterationTime)+1;
	int iterationCount = 0;;
	int GameTime = 0;
	const int max_lives = 3;
	      int lives = max_lives;
    const int health_per_reset=1;
	      int currhealth = health_per_reset;
		  int falldamage_height = 5;
		  int explosion_damage_radius = 2;
		  bool usedHammer = false;
		 
	bool newGame = true;
    bool pause_game = false;
	bool printed_instructions = false;//check if already printed instructions
	//health pos in board
	static constexpr int  health_displayX = 76;
	static constexpr int  health_displayY = 2;
	int barrel_waitTime = 15;
	int curr_barrel_waitTime = barrel_waitTime;
	//screen time of specific boards
	const int GO_screentime = 2000;
	const int Victory_screentime =4000;
	const int Error_screentime = 2000;
	enum class  gameState{menu,level,reset,game_over,victory,exit_game,instructions,level_select,manage_errors,get_levelInput};//game states
	gameState currstate =gameState:: menu;
	int currLevel = 0;
	Board pBoard;
	enum class errorType{not_found,bad_board,general};
	errorType currError = errorType::general;
	std::vector <Barrel> barrel;
	std::vector <Ghost> ghost;
	std::vector<std::string> boardfileNames;
	int fileamount = 0;
	
	static constexpr char damagecollisions[] = { 'O', 'x'};
	static const int col_length = 2;

public:

	void main_game();
	void level_1();
	void PauseGame();
	bool HealthCheck();
	void inMenu();
    void PrintLives() const;
	void ResetLevel();
	void resetGhosts();
	void printErrors();
	void getLevelInput();
	void LevelSelect();
	void MoveBarrels(Pointmovement player_movement);
	void MoveGhosts();
	void checkGhostsColliding();
	void checkAllGhostsIfHit(Pointmovement player_point);
	void checkAllBarrelsIfHit(Pointmovement player_point);
	void printFileNames();
    const int getFileIndexStart() const;
    const int getFileIndexend(int fileamount)const;
	void printTimeScore();
	void printGameInfo() const;
	void printLevelInput(char inputstr[]) const;
	bool checkLevelInput(char input[], int fileamount);
	bool switchLevelScreen(char key);
	void DamageTaken(Pointmovement player_movement);
	void FallDamageTaken(Pointmovement player_movement);
	void ExplosionDamageTaken(int barrelx, int barrely, Pointmovement player_movement);
	bool IsPaulineReached(Pointmovement player_movement);
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	bool getBoardData();
};
#pragma once
#include "Board.h"
#include "utils.h"
#include "movement.h"
#include "Abilities.h"
#include "Mario.h"
#include "Barreles.h"
#include "Ghost.h"
#include "ClimbingGhost.h"
#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>
#include <string>
#include <time.h>
#include <cstdlib>

class Game {
protected:
	//game mode related
	bool isLoad = false;
	bool isSave = false;
	bool isSilent = false;

	//playable character related
	struct StartCoord { int x=10, y=22; }; // inner private struct
	struct GhostInfo { char type; StartCoord position; GhostInfo(char ghostType, const StartCoord& pos)
		: type(ghostType), position(pos) {} };
	static constexpr int PcharCount = 9;
	static constexpr char PlayableChars[] = { '@','$','&','H','O','x','X','L','p'};
	enum class PlayableChar { player_char, pauline_char,dk_char, ladder_char, barrel_char, ghost_char,climbing_ghost_char,legend_char, hammer_char };
	StartCoord playerStart,barrelStart,paulineCoord,legendCoord,hammerCoord;
	
	char PCharsAmount[PcharCount] = {};
	//player inputs
	const char GoRight_LevelSelect = 'd';
	const char GoLeft_LevelSelect = 'a';
	const char enterGame = '1';
	const char viewInstructions = '8';
	const char exitGame = '9';
	static constexpr int ESC = 27;
	//game parameters
	
	int maxFilesPerScreen = 30;
	int levelSelectScreenIndex = 0;
    int iterationTime = 80;
	 int iterationUntilSec = 15;
	
	int scoreIterationCount = 0;
	int GameTime = 0;
	const int max_lives = 3;
	      int lives = max_lives;
    const int health_per_reset=1;
	      int currhealth = health_per_reset;
		  int falldamage_height = 5;
		  int explosion_damage_radius = 2;
		  bool usedHammer = false;
		 static constexpr char damagecollisions[] = { 'O', 'x', 'X'};
	static const int col_length = 3;
	bool newGame = true;
    bool pause_game = false;
	//check if already printed instructions
	bool printed_instructions = false;
	int barrel_waitTime = 20;
	int curr_barrel_waitTime = barrel_waitTime;
	//screen time of specific boards
	const int GO_screentime = 2000;
	const int Victory_screentime =4000;
	const int Error_screentime = 2000;
	enum class  gameState{menu,level,reset,game_over,victory,exit_game,
		instructions,level_select,manage_errors,get_levelInput,requestNextLevel};//game states
	gameState currstate =gameState:: menu;
	int currLevel = 0;
	Board pBoard;
	//error managment
	enum class errorType{not_found,bad_board,general,saveMode,LoadMode,stepMismatch};
	errorType currError = errorType::general;
	// data structures
	std::vector<GhostInfo> ghostData;
	std::vector <Barrel> barrel;
	std::vector<std::unique_ptr<Ghost>> ghost;
	std::vector<std::string> boardfileNames;
	int fileamount = 0;
	
	

public:
	
	virtual void main_game();
	virtual void level();
	virtual void printErrors();
	virtual void seedSrand() { std::srand((int)time(NULL)); }
	virtual void getPlayerInput(char& key);
	virtual void printTimeScore();
	virtual void printGameInfo() const;
	virtual bool HealthCheck();
	virtual bool stopGameLoop() { return false; }
	virtual void doAfterLoop() {};
	void PauseGame();
	void inMenu();
	bool requestNextLevel();
	void ResetLevel(Pointmovement& player_movement);
	void resetGhosts(Pointmovement& player_movement);
	void getLevelInput();
	bool getBoardData();
	void LevelSelect();
	void MoveGhosts();
	void checkGhostsColliding();
	void printFileNames();
    const int getFileIndexStart() const;
	void MoveBarrels(Pointmovement player_movement);
	void checkAllGhostsIfHit(Pointmovement player_point);
	void checkAllBarrelsIfHit(Pointmovement player_point);
    const int getFileIndexend(int fileamount)const;
	void printLevelInput(char inputstr[]) const;
	bool checkLevelInput(char input[], int fileamount);
	bool switchLevelScreen(char key);
	void DamageTaken(Pointmovement player_movement);
	void FallDamageTaken(Pointmovement player_movement);
	void ExplosionDamageTaken(int barrelx, int barrely, Pointmovement player_movement);
	bool IsPaulineReached(Pointmovement player_movement);
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	
};
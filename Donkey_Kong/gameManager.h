#pragma once
#include "Board.h"
#include "utils.h"
#include "movement.h"
#include "Mario.h"
#include "Barreles.h"


#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>



class Game {
	//const chars
    static constexpr char player_char = '@';
	static constexpr char pauline_char = '$';
	static constexpr char ladder_char = 'H';
	static constexpr char barrel_char = 'O';

	static constexpr int ESC = 27;
	//game parameters
	const int max_lives = 3;
	      int lives = max_lives;
    const int health_per_reset=1;
	      int currhealth = health_per_reset;
		  int falldamage_height = 5;
		  int explosion_damage_radius = 2;

	bool newGame = true;
    bool pause_game = false;
	bool printed_instructions = false;//check if already printed instructions
	//health pos in board(just for one level for now)
	static constexpr int  health_displayX = 76;
	static constexpr int  health_displayY = 2;
	int barrel_waitTime = 20;
	int curr_barrel_waitTime = barrel_waitTime;
	//screen time of specific boards
	int GO_screentime = 2000;
	int Victory_screentime =4000;
	 enum  gameState{menu,level,reset,game_over,victory,exit_game,instructions};//game states
	 int currstate = menu;
	 Board pBoard ;
	
	
	static constexpr char damagecollisions[] = { 'O'};
	static const int col_length = 1;
public:
	
    
	
	void main_game();
	void level_1();
	void PauseGame();
	bool HealthCheck();
	void inMenu();
    void PrintLives();
	void DamageTaken(Pointmovement player_movement);
	void FallDamageTaken(Pointmovement player_movement);
	void ExplosionDamageTaken(int barrelx, int barrely, Pointmovement player_movement);
	bool IsPaulineReached(Pointmovement player_movement);


	
	
	
};
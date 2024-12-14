#pragma once

#include <iostream>


#include <windows.h>
#include <conio.h>
#include <vector>

#include "Board.h"
#include "utils.h"
#include "movement.h"
#include "Mario.h"
#include "gameManager.h"
//#include "Mario_abilities.h"
#include "Barreles.h"
#define MAX_HEALTH 3

class Game {
	/*static constexpr int MAX_X = 4;
	static constexpr int MAX_Y = 3;
	static constexpr int MAX_Z = 3;*/
	static constexpr int ESC = 27;
	int healthPosX = 75;
	int healthPosY = 2;
	int health = MAX_HEALTH;
	bool newGame = true;
	int currhealth = 0;
	bool pause_game = false;
	int damage_collision_checkX = 0;
	int damage_collision_checkY = 0;
	bool check_collision_dir = false;
	/*const char* healthDisplay[MAX_Y][MAX_Z] = {
		{" __ ",
		 " __|",
		 " __|"},
		{" __ ",
		 " __|",
		 "|__ "},
		{"  |",
		 "  |",
		 "  |",}
	};
	char currentHealthDisplay[MAX_Y][MAX_X + 1]; // +1 for null terminator*/
	Board pBoard ;
	
public:
	
    static constexpr char player_char = '@';
	static constexpr char ladder_char = 'H';
	static constexpr char damagecollisions[] = { 'O' };
	int col_length = 1;
	void draw(int c)  const {
		gotoxy(healthPosX, healthPosY);
		std::cout << c;
		std::cout.flush();
	}
	void main_game();
	void level();
	
	void resetGame();
	void resetHealth();
	void lowerHealth();
	void printGame();
	void DamageTaken(Pointmovement player_movement);
	
	void printHealth() const {
		draw(health);
	}

	void getCharInBoard(int x, int y, char into) {
		//into = pBoard->getChar(x, y);
	}

	/*char getChar(int x, int y) const {
		return currentBoard[y][x];
	}*/
	
};
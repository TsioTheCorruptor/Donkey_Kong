#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"

class Barrel {

	 char barrel_char = 'O';
	 static constexpr char explosion_char = '*';
	 Pointmovement barrel_movement;
	 Board* pBoard = nullptr;
	int prev_dirX=0;
	int prev_dirY=0;
    int start_posX=0 ;
    int start_posY=0;
	int lengthFallen=0;
	

	static constexpr char collisions[] = { '@','Q','<','=','>'};
	enum coll_hit{player,wall,floor_left,neutral_floor,floor_right };//order has to stay

   static constexpr  int col_length = 5;
   static constexpr int explode_delay = 2;
     bool explosion_started=false;
	 bool explosion_ended = false;
	
	 int explode_stage = 0;
	 bool stop_movement = false;
 public:
	
	 Barrel(  Pointmovement point, Board& board) :
		 barrel_movement(point), pBoard(&board) {}

	//Barrel() : prev_dirX(0), prev_dirY(0), lengthFallen(0), exploded(false) {}

	

	

	void checkAndMoveBarrel();

	

	char get_barrel_char() {
		return barrel_char;
	}
	void set_barrel_char(const char chr) {
		barrel_char = chr;
	}
	
	void getBarrelDir(const char colliders[]);

	const bool isExploded() {
		return explosion_ended;
	}
	const bool isExploding() {
		return explosion_started;
	}
	void DrawBarrel();
	const int GetposX()
	{
		return barrel_movement.GetX();
	}
	const int GetposY()
	{
		return barrel_movement.GetY();
	}
	
};
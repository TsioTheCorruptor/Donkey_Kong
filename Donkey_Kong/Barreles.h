#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"

class Barrel {

	 char barrel_char = 'O';
	 Pointmovement barrel_movement;
	 Board* pBoard = nullptr;
	int prev_dirX=0;
	int prev_dirY=0;
    int start_posX=0 ;
    int start_posY=0;
	int lengthFallen=0;
	

	static constexpr char collisions[] = { '@','Q','<','=','>'};
	enum coll_hit{player,wall,floor_left,neutral_floor,floor_right };//order has to stay

     int col_length = 5;
     bool exploded=false;
	 int explode_delay = 5;
	 int explode_stage = 0;
	 bool stop_movement = false;
 public:
	
	 Barrel( int posx,  int posy, Pointmovement point, Board& board) :start_posX(posx),
		 start_posY(posy), barrel_movement(point), pBoard(&board) {
		
	 }

	//Barrel() : prev_dirX(0), prev_dirY(0), lengthFallen(0), exploded(false) {}

	

	

	void checkAndDrawBarrel();

	

	char get_barrel_char() {
		return barrel_char;
	}
	void set_barrel_char(const char chr) {
		barrel_char = chr;
	}
	
	void getBarrelDir(const char colliders[]);

	bool isExploded() {
		return exploded;
	}
	void DrawBarrel();
	
};
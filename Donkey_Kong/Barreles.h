#pragma once

#include <iostream>
#include "movement.h"
#include "board.h"

class Barrel : public Pointmovement {

    char barrel_char = 'O';
	CHAR playerChar = '@';
	static constexpr char explosion_char = '*';
	Board* pBoard = nullptr;
	//direction in previous floor
	int prev_dirX=0;
	int prev_dirY=0;
	//start position
    int start_posX=0 ;
    int start_posY=0;
	
	static constexpr char collisions[] = { '@','Q','<','=','>'};
	enum class coll_hit{player,wall,floor_left,neutral_floor,floor_right };//order has to stay
	static constexpr  int col_length = 5;

    //iterations from explosion start to explosion end
    static constexpr int explode_delay = 2;
	int explode_stage = 0;
	bool explosion_started=false;
	bool explosion_ended = false;
	bool stop_movement = false;//stop barrel movement

 public:
	 
	 Barrel(const char move_char, int posx, int posy, Board& board, char player_char) :
		 Pointmovement(move_char, posx, posy, board), pBoard(&board), playerChar(player_char) {}

	void checkAndMoveBarrel();

	char get_barrel_char() const{
		return barrel_char;
	}

	void set_barrel_char(const char chr) {
		barrel_char = chr;
	}
	
	void getBarrelDir(const char colliders[]);

	const bool isExploded() const{
		return explosion_ended;
	}

	const bool isExploding() const{
		return explosion_started;
	}	

	bool checkBarrelHit(Pointmovement mario) const;
};
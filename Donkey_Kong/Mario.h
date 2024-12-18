#pragma once
#include <iostream>
#include "movement.h"
#include "board.h"

class Mario {

 char mario_char = '@';
 char ladder_char ='H';
 static constexpr char upkey = 'w';
 static constexpr char downkey = 'x';
 struct Jump_InOrder { int x, y; };
 bool go_below_ground = false;
 
 int move_stage = 0;
 //jump directions
 static constexpr Jump_InOrder jump_inorder_right[] = { {0, -1}, {1, -1},{1,0},{1,1}, {0,1} };
 static constexpr int move_count_right = 5;

 static constexpr Jump_InOrder jump_inorder_left[] = { {0, -1}, {-1, -1},{-1,0}, {-1, 1}, {0,1}};
 static constexpr int move_count_left = 5;

 static constexpr Jump_InOrder jump_inorder_neutral[] = { {0, -1},{0, -1} };
 static constexpr int move_count_neutral = 2;

                 bool isjumping = false;
                 bool ladder_up = true;//going up or down ladder
       Pointmovement* player_movement = nullptr;
               Board* board = nullptr;
			   //save dir for after jump
			   int savedirX = 0;
               int savedirY = 0;

 static constexpr char collisions[4] = { 'Q','<','=','>'};//mario collisions
 static constexpr int col_length = 4;
enum move_type {no_moves,jumping,ladder};//mario states
	move_type curr_move = no_moves;
public:
	
	



	Mario(const char player_char,const char ladder_Char,Pointmovement& player_Movement,Board& pBoard ) : 
		mario_char(player_char),ladder_char(ladder_Char), player_movement(&player_Movement), board(&pBoard) {}

	
	void Jump();
	void InLadder();
	void DoMarioMoves(int key);
    void Jump_InDirection(const Jump_InOrder* order, int length,int currdirx,int currdiey);
	const int GetSavedDirX()const { return savedirX; }
	const int GetSavedDirY()const { return savedirY; }
	const char* GetCollisionArray()const { return collisions; }
	const int GetCollisionArrayLength()const { return col_length; }
	bool is_jumping()
	{
		return isjumping;
	}
	int GetMoveType(char key);

};
﻿#pragma once

//#include "healthManager.h"
#include "utils.h"
class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	const char* originalBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q         H                       .--.                          . .            Q", // 1
		  "Q  OO     H   !                .-(    ).            __         (/`/)  X        Q", // 2
		  "Q  OO   & H   $               (___.__)__)        ._(  ).        `//            Q", // 3
		  "Q =======>>============                         (__.___)         v             Q", // 4
		  "Q                   H                                                          Q", // 5
		  "Q                   H                                         *                Q", // 6
		  "Q       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>             / `               Q", // 7
		  "Q                                 H                         /   `              Q", // 8
		  "Q                                 H                        /_____`             Q", // 9
		  "Q                                 H                           |                Q", // 10
		  "Q                      <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<========Q", // 11
		  "Q         O                                       H                            Q", // 12
		  "Q         |                                       H                            Q", // 13
		  "Q       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                            Q", // 14
		  "Q                            H                                                 Q", // 15
		  "Q                            >>>>>>>>>>>>>>>>>>>>>>>                           Q", // 16
		  "Q          ( )                                           H                     Q", // 17
		  "Q        (   )                                           H                     Q", // 18
		  "Q         ( )      <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      Q", // 19
		  "Q         _||                                  H                ~~ |           Q", // 20
		  "Q        /___`                                 H                |__|__________|Q", // 21
		  "Q       /_____`                                H               |   |__________|Q", // 22
		  "Q       |   []|                                H                --- 0   0   0  Q", // 23
		  "================================================================================"  // 24
	};
	const char* mainMenu[MAX_Y] = {
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", // 0
		"(                                                                              (", // 1
		")                                                                              )", // 2
		"(     ██╔══██╗██╔═══██╗████╗  ██║██║ ██╔╝██╔════╝╚██╗ ██╔╝                     (", // 3
		")     ██║  ██║██║   ██║██╔██╗ ██║█████╔╝ █████╗   ╚████╔╝                      )", // 4
		"(     ██║  ██║██║   ██║██║╚██╗██║██╔═██╗ ██╔══╝    ╚██╔╝                       (", // 5
		")     ██████║ ╚██████╔╝██║ ╚████║██║  ██╗███████╗   ██║                        )", // 6
		"(     ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝   ╚═╝                        (", // 7
		")                                                                              )", // 8
		"(                                ██╗  ██╗ ██████╗ ███╗   ██╗ ██████╗           (", // 9
		")       __________________       ██║ ██╔╝██╔═══██╗████╗  ██║██╔════╝           )", // 10
		"(      | Start a New Game |      █████╔╝ ██║   ██║██╔██╗ ██║██║  ███╗          (", // 11
		")       ------------------       ██╔═██╗ ██║   ██║██║╚██╗██║██║   ██║          )", // 12
		"(                                ██║  ██╗╚██████╔╝██║ ╚████║╚██████╔╝          (", // 13
		")       Instructions:            ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝           )", // 14
		"(                                                                              (", // 15
		")       - Avoid barrels                                                        )", // 16
		"(                                                                              (", // 17
		")       - Save Pauline                                                         )", // 18
		"(                                                                              (", // 19
		")       - Keys: LEFT->A, RIGHT->D, UP/JUMP->W, DOWN->X, STAY->S                )", // 20
		"(                                                                    ______    (", // 21
		")                                                                   | Exit |   )", // 22
		"(                                                                    ------    (", // 23
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  // 24
	};

	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	//Health* pHealth = nullptr;
public:
	void reset();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
	char getOgChar(int x, int y) const {
		return originalBoard[y][x];
	}
	
	void setChar(int x,int y,char chartoset)
	{
		currentBoard[y][x] = chartoset;
	}
	void draw_InPosition(int xpos, int ypos, char chr)
	{
		gotoxy(xpos, ypos);
		std::cout << chr;
		//setChar(xpos, ypos, chr);
		std::cout.flush();
	}

};



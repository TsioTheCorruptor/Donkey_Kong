#pragma once


#include "utils.h"
#include <cstring>
#include <iostream>
#include <fstream>


class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	int currLevelBoardHeight = 0;
	
	int screenPrintDelay = 30;//delay for printing each board line
	const char* LevelBorders[MAX_Y+2] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                                Q", // 1
		  "Q                                                                                Q", // 2
		  "Q                                                                                Q", // 3
		  "Q                                                                                Q", // 4
		  "Q                                                                                Q", // 5
		  "Q                                                                                Q", // 6
		  "Q                                                                                Q", // 7
		  "Q                                                                                Q", // 8
		  "Q                                                                                Q", // 9
		  "Q                                                                                Q", // 10
		  "Q                                                                                Q", // 11
		  "Q                                                                                Q", // 12
		  "Q                                                                                Q", // 13
		  "Q                                                                                Q", // 14
		  "Q                                                                                Q", // 15
		  "Q                                                                                Q", // 16
		  "Q                                                                                Q", // 17
		  "Q                                                                                Q", // 18
		  "Q                                                                                Q", // 19
		  "Q                                                                                Q", // 20
		  "Q                                                                                Q", // 21
		  "Q                                                                                Q", // 22
		  "Q                                                                                Q", // 23
		  "=================================================================================="  // 24
	};
	const char* mainMenu[MAX_Y] = {
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", // 0
	"(    ________     ______   _____  ___  __   ___ _______ ___  ___               (", // 1
	")   |        `   /      ` (`    `|   `|/ | /   )        |    `/ |              (", // 2
	"(   (.  ___  :) // ____  `|.``   `    (: |/   (: ______)`   `  /               (", // 3
	")   |: `   ) ||/  /    ) :): `.   ``  |    __/ `/    |   ``  `/                )", // 4
	"(   (| (___` |(: (____/ //|.  `    `. (// _  ` // ___)_  /   /                 (", // 5
	")   |:       :)`        / |    `    ` |: | `  (:       |/   /                  )", // 6
	"(   (________/  ` _____/   `___|`____`|__|  `__)_______)___/                   (", // 7
	")                                                                              )", // 8
	"(              _                __   ___  ______   _____  ___   _______        (", // 9
	")       Press |1| to           |/ | /   )/      ` (`    `|   ` /   _   |       )", // 10
	"(              -               (: |/   /// ____  `|.``   `    (: ( `___)       (", // 11
	")       Start a New Game       |    __//  /    ) :): `.   ``  |`/ `            )", // 12
	"(                              (// _  (: (____/ //|.  `    `. |//  ` ___       (", // 13
	")                        _     |: | `  `        / |    `    ` (:   _(  _|      )", // 14
	"(    Instructions-Press |8|:   (__|  `__) _____ / `___ | `____`)`_______)      (", // 15
	")                        -                                                     )", // 16
	"(                                                                              (", // 17
	")                                                                              )", // 18
	"(                                                                              (", // 19
	")                                                                              )", // 20
	"(                                                           _                  (", // 21
	")                                                    Press |9| to Exit Game    )", // 22
	"(                                                           -                  (", // 23
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  // 24
	};
	const char* PauseGame[MAX_Y] = {
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",//0
	"         .         .                                     .             *     .  ",//1
	"     |         *       *            *               .                __         ",//2
	"    -*-                       .                  *                  // `        ",//3
	"     |      .                                                      |-   `       ",//4
	"                  *        .         .                *            ||       .   ",//5
	"         .                              |                 .        ` `_/        ",//6
	"    .             .           .        -*-                          `__/        ",//7
	"      .    *          *                 |             *                         ",//8
	"                                                   .          *         .       ",//9
	"                             *                          .                       ",//10
	"    .     .                        GAME PAUSED                           *      ",//11
	"       *      .    |           .                          *                     ",//12
	"                  -*-                     .         .            .    |      .  ",//13
	"                   |         *  .    .                               -*-        ",//14
	"    .                                    *                            |         ",//15
	"      .       .      .                                  .    .               *  ",//16
	"           *                      *      .        *          *                  ",//17
	"                .        *                                                      ",//18
	"    .                                         .            *                    ",//19
	"        |                      *                   .     .                 |    ",//20
	"       -*-      *        .               .                                -*-   ",//21
	"   .    |                         .                             *          |    ",//22
	"                  .                            *    .                           ",//23
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",//24

	};
	const char* gameOver[MAX_Y] = {
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",//0
	"                                                                                ",//1
	"                                                                                ",//2
	"           .                                                      .             ",//3
	"         .n                   .                 .                  n.           ",//4
	"   .   .dP                  dP                   9b                 9b.    .    ",//5
	"  4    qXb         .       dX                     Xb       .        dXp     t   ",//6
	" dX.    9Xb      .dXb    __                         __    dXb.     dXP     .Xb  ",//7
	"  9XXb._       _.dXXXXb dXXXXbo.                 .odXXXXb dXXXXb._       _.dXXP ",//8
	"   9XXXXXXXXXXXXXXXXXXXVXXXXXXXXOo.           .oOXXXXXXXXVXXXXXXXXXXXXXXXXXXXP  ",//9
	"    `9XXXXXXXXXXXXXXXXXXXXX'~   ~`OOO8b   d8OOO'~   ~`XXXXXXXXXXXXXXXXXXXXXP'   ",//10
	"      `9XXXXXXXXXXXP' `9XX'   GAME   `98v8P'   OVER   `XXP' `9XXXXXXXXXXXP'     ",//11
	"          ~~~~~~~       9X.          .db|db.          .XP       ~~~~~~~         ",//12
	"                          )b.  .dbo.dP'`v'`9b.odb.  .dX(                        ",//13
	"                        ,dXXXXXXXXXXXb     dXXXXXXXXXXXb.                       ",//14
	"                       dXXXXXXXXXXXP'   .   `9XXXXXXXXXXXb                      ",//15
	"                      dXXXXXXXXXXXXb   d|b   dXXXXXXXXXXXXb                     ",//16
	"                      9XXb'   `XXXXXb.dX|Xb.dXXXXX'   `dXXP                     ",//17
	"                       `'      9XXXXXX(   )XXXXXXP      `'                      ",//18
	"                                XXXX X.`v'.X XXXX                               ",//19
	"                                XP^X'`b   d'`X^XX                               ",//20
	"                                X. 9  `   '  P )X                               ",//21
	"                                `b  `       '  d'                               ",//22
	"                                 `             '                                ",//23
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",//24
	};

	const char* gameWon[MAX_Y] = {
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", // 0
	"                                                                                ", //1
	"                                                                                ",//2
	"     ,-**-.  .-**-.          .+._                                               ",//3
	"    /   -. `/   -. `      (^`/^`/^)     __   _____ ___ _____ ___  _____   ___   ",//4
	"   (                )      `@*@*@/      ` ` / /_ _/ __|_   _/ _ `| _ ` ` / / |  ",//5
	"    `              /       {_____}       ` V / | | (__  | || (_) |   /` V /|_|  ",//6
	"     `            /       (((( ))))       `_/ |___`___| |_| `___/|_|_` |_| (_)  ",//7
	"      `.        ,'       (((^ . ^)))                    |_|            |_|      ",//8
	"        `.    ,'         (((`_~_/)))                                            ",//9
	"          `.,'           (((_) (_)))                                            ",//10
	"                        /((( ` / )))`                                           ",//11
	"                       / (((  ^  ))) `                                          ",//12
	"                      / / ((  ^  )) ` `                                         ",//13
	"                     ( (   `  ^  /   ) )                                        ",//14
	"                      ` `   )www(   / /            |                   ___      ",//15
	"                       ``` /     ` //'            -+-             +   | M |     ",//16
	"                         /'       ``              _|_            {@}  _|=|_     ",//17
	"                        /           `            /___`          /( )`  ( )      ",//18
	"                       /             `        .---'-'---.      /((~))`/`        ",//19
	"                      /               `      /___________`     ~~/@`~~`|_|/     ",//20
	"                     /                 `      | A /^` A |       /   `  |||      ",//21
	"                     |                 |      |   | |   |      /~@~@~` |||      ",//22
	"                      `-----......-----'     _|___|_|___|_____/_______`|||___   ",//23
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",//24

	};
	const char* EmptyBoard[MAX_Y] = {//to make new boards easier
		"                                                                                ", // 0
		"                                                                                ", //1
		"                                                                                ",//2
		"                                                                                ",//3
		"                                                                                ",//4
		"                                                                                ",//5
		"                                                                                ",//6
		"                                                                                ",//7
		"                                                                                ",//8
		"                                                                                ",//9
		"                                                                                ",//10
		"                                                                                ",//11
		"                                                                                ",//12
		"                                                                                ",//13
		"                                                                                ",//14
		"                                                                                ",//15
		"                                                                                ",//16
		"                                                                                ",//17
		"                                                                                ",//18
		"                                                                                ",//19
		"                                                                                ",//20
		"                                                                                ",//21
		"                                                                                ",//22
		"                                                                                ",//23
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",//24

	};
	 char Level[MAX_Y][MAX_X +1];
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	char currentstaticBoard[MAX_Y][MAX_X + 1];
	
public:
	
	void reset() ;
	void print() const;
	void printEmpty() const;
	void printMenu() const ;
	void printPause()const;
	void printGameOver()const;
	void printVictory()const;
	void printInstructions()const;
	bool load(const std::string& filename);

	const char getChar(int x, int y) const {
		if (y >= MAX_Y)
			return '=';
		if (x >= MAX_X||x < 0||y<0)
			return 'Q';
		

		
				 return currentBoard[y][x];
	}
	const char getOgChar(int x, int y) const {
		
		if (y >= MAX_Y)
			return '=';
		if (x >= MAX_X || x < 0 || y < 0)
			return 'Q';
				return Level[y][x];

	}
	 void setOgChar(int x, int y,char chr)  {
		 Level[y][x] = chr;
		
		
	}
	
	void setChar(int x,int y,char chartoset)
	{
		currentBoard[y][x] = chartoset;
	}
	const char getBorderChar(int x, int y) const {
		int extraleft = 0;
		int extraright = 0;
		return LevelBorders[y][x];
	}
	void draw_InPosition(int xpos, int ypos, char chr)
	{
		gotoxy(xpos, ypos);
		std::cout << chr;
		setChar(xpos, ypos, chr);
		std::cout.flush();
	}
	
};



#include "Board.h"





void Board::reset() {
	
	

		for (int i = 0; i < MAX_Y; i++) {
			memcpy(currentBoard[i], Level[i], MAX_X + 1);
		}
}

void Board::print() const {
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
	
}
void Board::printPause()const 
{
	
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << PauseGame[i] << '\n';
	}
	std::cout << PauseGame[MAX_Y - 1];
}
void Board::printMenu()const
{

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << mainMenu[i] << '\n';
	}
	std::cout << mainMenu[MAX_Y - 1];
}
void Board::printGameOver()const
{

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << gameOver[i] << '\n';
	}
	std::cout << gameOver[MAX_Y - 1];
}
void Board::printVictory()const
{

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << gameWon[i] << '\n';
	}
	std::cout << gameWon[MAX_Y - 1];
}
void Board::printInstructions()const
{
	gotoxy(0, 16);
	std::cout << R"(
(    - Avoid Barrels                                                         
)    - Save Pauline                                                          
(    - Keys: LEFT->A, RIGHT->D, UP/JUMP->W, DOWN->X, STOP->S)";
               
}






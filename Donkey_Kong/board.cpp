#include "Board.h"

const char Board::getChar(int x, int y) const {
	if (y >= MAX_Y)
		return '=';
	if (x >= MAX_X || x < 0 || y < 0)
		return 'Q';
	return currentBoard[y][x];
}
const char Board::getOgChar(int x, int y) const {
	if (y >= MAX_Y)
		return '=';
	if (x >= MAX_X || x < 0 || y < 0)
		return 'Q';
	return Level[y][x];

}

void Board::draw_InPosition(int xpos, int ypos, char chr) {
	gotoxy(xpos, ypos);
	std::cout << chr;
	setChar(xpos, ypos, chr);
	std::cout.flush();
}
void Board::reset() {

	//memcpy(currentBoard,Level, MAX_Y * (MAX_X + 1));
	for (int i = 0; i < MAX_Y; i++) 
	memcpy(currentBoard[i], Level[i], MAX_X + 1);
}
void Board::print() const {

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y-1 ; i++) {
		Sleep(screenPrintDelay);
		std::cout << currentBoard[i]<<'\n';
	}
	std::cout << currentBoard[MAX_Y -1];
}
void Board::printPause() const {

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << PauseGame[i] << '\n';
	}
	std::cout << PauseGame[MAX_Y - 1];
}
void Board::printEmpty() const{

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << EmptyBoard[i] << '\n';
	}
	std::cout << EmptyBoard[MAX_Y - 1];
}
void Board::printMenu() const {

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << mainMenu[i] << '\n';
	}
	std::cout << mainMenu[MAX_Y - 1];
}
void Board::printGameOver() const {

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << gameOver[i] << '\n';
	}
	std::cout << gameOver[MAX_Y - 1];
}
void Board::printVictory() const {

	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		Sleep(screenPrintDelay);
		std::cout << gameWon[i] << '\n';
	}
	std::cout << gameWon[MAX_Y - 1];
}
void Board::printInstructions() const{
	gotoxy(0, 16);
	std::cout << R"(
(    - Avoid Barrels                                                         
)    - Save Pauline                                                          
(    - Keys: LEFT->A, RIGHT->D, UP/JUMP->W, DOWN->X, STOP->S)";        
}
bool Board::load(const std::string& filename) {

	std::ifstream screen_file(filename);
	if (!screen_file.is_open()){
		return false;
	}

	int curr_row = 0;
	int curr_col = 0;
	int last_col = 0;
	int last_row = 0;
	char c;
	bool stopGettingData = false;
	while ( !screen_file.get(c).eof() &&curr_row < MAX_Y) {
		if ( c == '\n') {
			if (curr_col < MAX_X) {
				// add spaces for missing cols !screen_file.get(c).eof() &&
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(Level[curr_row] + curr_col, std::string(MAX_X - curr_col , ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if(curr_col<MAX_X)
			Level[curr_row][curr_col++] = c;
		last_col = curr_col;
	}
	if (curr_row < MAX_Y ){
		last_row = curr_row;
#pragma warning(suppress : 4996) // to allow strcpy
		strcpy(Level[last_row] + last_col, std::string(MAX_X - last_col, ' ').c_str());
		// add a closing frame
		for (int afterrow = last_row+1; afterrow< MAX_Y; afterrow++){
#pragma warning(suppress : 4996) // to allow strcpy
			strcpy(Level[afterrow] , std::string(MAX_X , ' ').c_str());	
		}
	}
	return true;
}







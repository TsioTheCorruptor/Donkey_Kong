
#include "gameManager.h"
#include "gameModes.h"

int main(int argc, char** argv) {
	Game* game=GameModes::getMode(argv,argc);
	game->main_game();	
	delete game;
	
}



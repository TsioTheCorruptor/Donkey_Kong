#pragma once
#include "gameManager.h"
#include "LoadMode.h"
#include "SaveMode.h"
#include "SilentMode.h"
class GameModes {
	
public:
	~GameModes() = default;
	static Game* getMode(char** modeString, int stringcount);
	
};

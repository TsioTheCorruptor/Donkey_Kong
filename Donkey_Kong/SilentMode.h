#pragma once
#include "gameManager.h"
#include "LoadMode.h"
class SilentMode :public LoadMode {
public:
	SilentMode() { 
		isSilent = true;
		iterationTime = 0;
		pBoard.allowPrint(false);
	}
	virtual void printTimeScore();
	virtual void printGameInfo()const {};

};
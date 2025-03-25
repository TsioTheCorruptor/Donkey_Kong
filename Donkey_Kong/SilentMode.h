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
	virtual ~SilentMode() {}
	 void printTimeScore()override;
	 void printGameInfo()const override {};

};
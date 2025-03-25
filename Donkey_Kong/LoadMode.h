#pragma once
#include "gameManager.h"
class LoadMode :public Game {
	struct inputInfo {
		int iteration = 0;
		char input = ' ';
		inputInfo(int iteration_, char key) :iteration(iteration_), input(key) {}
	};
	int iterationCount = 0;//curr iteration
	int maxiteration = 0;//the max iteration of curr level
	std::vector<inputInfo> inputToSave;
	std::vector<inputInfo> resultToCheck;
	int inputcount = 0;
	//size of file data
	int stepsize = 0;
	int resultsize = 0;
	int randomseed = 0;
	int stageResetCount = 0;
	int currScoreToCheck = 0;
public:
	LoadMode() { isLoad = true; }
	virtual ~LoadMode(){}
	 void main_game()override;
	 bool checkDeathResult() ;
	void printErrors () override;
	 void seedSrand()override { std::srand(randomseed); }
	 void getPlayerInput(char& key)override;
	bool HealthCheck()override;
	bool stopGameLoop()override;
	std::string getStepsFileName()const;
	bool setupLoad();
	bool checkResult() { return true; };
	std::string getResultFileName()const;
	void SilentSucces();


};
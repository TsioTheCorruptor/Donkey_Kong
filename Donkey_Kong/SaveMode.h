#pragma once
#include "gameManager.h"

class SaveMode :public Game {
	struct inputInfo {
		int iteration = 0;
		char input = ' ';
		inputInfo(int iteration_,char key):iteration(iteration_),input(key){}
	};
	std::vector<inputInfo> inputToSave;
	std::vector<inputInfo> resultToSave;
	int iterationCount = 0;//curr iteration
	int randomseed=0;

public:
    SaveMode() { isSave = true;}
	virtual ~SaveMode(){}
	 void main_game()override;
	std::string getResultFileName()const;
	 void seedSrand()override { std::srand(randomseed); }
	 void getPlayerInput(char& key)override;
	 bool HealthCheck()override;
	std::string getStepsFileName()const;
	void saveData();
    void makeEmptyFiles()const;
	void setRandomSeed() {
		randomseed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	}

};
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
	int iterationCount = 0;
	int randomseed=0;

public:
    SaveMode() {
        isSave = true;
       /* // 1) Iterate over all files in the current directory
        namespace fs = std::filesystem;
        for (const auto& entry : fs::directory_iterator(fs::current_path()))
        {
            // 2) Check if the filename ends with .steps or .result
            auto path = entry.path();
            auto filenameStr = path.filename().string();

            // A simple approach to detect the endings:
            if (filenameStr.size() >= 6) // enough length for ".steps" or ".result"
            {
                // Check for ".steps" or ".result"
                if (filenameStr.rfind(".steps") == filenameStr.size() - 6 ||
                    filenameStr.rfind(".results") == filenameStr.size() - 8)
                {
                    // 3) Truncate the file to empty it
                    std::ofstream file(path, std::ios::out | std::ios::trunc);
                    if (!file.is_open())
                    {
                        std::cerr << "Warning: Failed to truncate " << filenameStr << std::endl;
                        Sleep(Error_screentime);
                    }
                    else
                    {
                        std::cout << "Truncated file: " << filenameStr << std::endl;
                    }
                }
            }
        }*/
    }
	
	virtual void main_game();
	//virtual void level();
	std::string getResultFileName();
	virtual void seedSrand() { std::srand(randomseed); }
	virtual void getPlayerInput(char& key);
	virtual bool HealthCheck();
	std::string getStepsFileName();
	void saveData();
	void setRandomSeed() {
		randomseed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	}

};
#include "gameModes.h"
Game* GameModes::getMode(char** modeString,int stringcount)
{
	
	if (stringcount > 1)
	{
if (strcmp(modeString[1], "-load") == 0) {
		if (stringcount > 2 )
		{
			if (strcmp(modeString[2], "-silent") == 0)
			{
            SilentMode* returnSilent = new SilentMode;
			if (returnSilent == nullptr)
				std::cout << "failed allocation!";
			return returnSilent;
			}
			
		}
		LoadMode* returnload = new LoadMode;
		if (returnload == nullptr)
			std::cout << "failed allocation!";
		return returnload;
	}
	else if (strcmp(modeString[1], "-save") == 0  ) {
		
		SaveMode* returnsave= new SaveMode;
		if (returnsave == nullptr)
			std::cout << "failed allocation!";
		return returnsave;
	}
	}
	
	 
		Game* returndefault = new Game;
		if (returndefault == nullptr)
			std::cout << "failed allocation!";
		return returndefault;
	
		

	
}
#ifndef _USER_INTERFACE_INCLUDE
#define _USER_INTERFACE_INCLUDE

#include "Text.h"
#include <string>

class UserInterface
{

public:
	UserInterface();
	~UserInterface();
	void init(string newScore, string newNumCoins, string nameLevel, string newTime);
	void render();
	void setScore(string newScore);
	void setNumCoins(string newNumCoins);
	void setNameLevel(string newNameLevel);
	void setTime(string newTime);
	void setNumLives(string newNumLives);


private:
	glm::ivec2 posScore, posNumCoins, posNameLevel, posTime, posNumLives;
	string score, numCoins, nameLevel, time, numLives;
	Text text;
};

#endif 


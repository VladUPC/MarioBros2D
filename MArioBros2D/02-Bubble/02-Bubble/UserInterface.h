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
	void setNumLifes(string newNumLifes);


private:
	glm::ivec2 posScore, posNumCoins, posNameLevel, posTime, posNumLifes;
	string score, numCoins, nameLevel, time, numLifes;
	Text text;
};

#endif 


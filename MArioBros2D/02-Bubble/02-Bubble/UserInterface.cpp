#include "UserInterface.h"

#define SCREEN_Y 16

#define TEXT_SIZE 22

#define TEXT_COLOR glm::vec4(1.0, 1.0, 1.0, 1.0)

UserInterface::UserInterface()
{

}

UserInterface::~UserInterface()
{

}

void UserInterface::init(string newScore, string newNumCoins, string newNameLevel, string newTime)
{
	score = newScore;
	posScore = glm::vec2(10, SCREEN_Y + 20);

	numCoins = newNumCoins;
	posNumCoins = glm::vec2(110, SCREEN_Y + 20);

	nameLevel = newNameLevel;
	posNameLevel = glm::vec2(250, SCREEN_Y + 20);

	numLives = "3";
	posNumLives = glm::vec2(400, SCREEN_Y + 20);

	time = newTime;
	posTime = glm::vec2(500, SCREEN_Y + 20);


	text.init("fonts/DroidSerif-Bold.ttf");
}

void UserInterface::render()
{


	text.render("MARIO", glm::vec2(posScore.x , SCREEN_Y+ 2), TEXT_SIZE, TEXT_COLOR);
	text.render(score, posScore, TEXT_SIZE, TEXT_COLOR);


	text.render("COINS", glm::vec2(posNumCoins.x, SCREEN_Y + 2), TEXT_SIZE, TEXT_COLOR);
	text.render(numCoins, posNumCoins, TEXT_SIZE, TEXT_COLOR);

	text.render("LIVES", glm::vec2(posNumLives.x, SCREEN_Y + 2), TEXT_SIZE, TEXT_COLOR);
	text.render(numLives, posNumLives, TEXT_SIZE, TEXT_COLOR);

	text.render("WORLD", glm::vec2(posNameLevel.x, SCREEN_Y + 2), TEXT_SIZE, TEXT_COLOR);
	text.render(nameLevel, posNameLevel, TEXT_SIZE, TEXT_COLOR);

	text.render("TIME", glm::vec2(posTime.x, SCREEN_Y + 2), TEXT_SIZE, TEXT_COLOR);
	text.render(time, posTime, TEXT_SIZE, TEXT_COLOR);

}

void UserInterface::setScore(string newScore)
{
	score = newScore;
}

void UserInterface::setNumCoins(string newNumCoins)
{
	numCoins = newNumCoins;
}

void UserInterface::setNameLevel(string newNameLevel)
{
	nameLevel = newNameLevel;
}

void UserInterface::setTime(string newTime)
{
	time = newTime;
}

void UserInterface::setNumLives(string newNumLives)
{
	numLives = newNumLives;
}
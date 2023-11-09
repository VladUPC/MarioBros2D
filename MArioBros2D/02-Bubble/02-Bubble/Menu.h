#ifndef MENU_INCLUDE
#define MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include <vector>
#include <string>
#include "SoundManager.h"




class Menu
{
public:
	Menu();

	~Menu();

	void init();
	void update(int deltaTime);
	void render();

private:
	ShaderProgram texProgram;
	int currentState;
	Texture spritesheet;
	Sprite* mainSprite;
	glm::mat4 projection;
	int menuState;


	void initShaders();
	void aplyState(int state);



};


#endif
#ifndef CREDITS_INCLUDE
#define CREDITS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include <vector>




class Credits
{
public:
	Credits();

	~Credits();

	void init();
	void update(int deltaTime);
	void render();

private:
	ShaderProgram texProgram;
	int currentState;
	Texture spritesheet;
	Sprite* mainSprite;
	glm::mat4 projection;


	void initShaders();
	void backToMenu();


};


#endif
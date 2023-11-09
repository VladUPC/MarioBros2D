#ifndef INSTRUCTIONS_INCLUDE
#define INSTRUCTIONS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include <vector>




class Instructions
{
public:
	Instructions();

	~Instructions();

	void init();
	void update(int deltaTime);
	void render();

private:
	ShaderProgram texProgram;
	Texture spritesheet;
	Sprite* mainSprite;
	glm::mat4 projection;


	void initShaders();
	void backToMenu();


};


#endif
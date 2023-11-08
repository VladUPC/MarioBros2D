#include "Credits.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glut.h>


#define SCREEN_X 32
#define SCREEN_Y 16




Credits::Credits()
{

}

Credits::~Credits()
{
	if (mainSprite != NULL) delete mainSprite;
}


void Credits::init()
{
	initShaders();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);



	spritesheet.loadFromFile("images/credits_bground.png", TEXTURE_PIXEL_FORMAT_RGBA);


	mainSprite = Sprite::createSprite(glm::ivec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)),
		glm::vec2(1.f, 1.f), &spritesheet, &texProgram);


	mainSprite->setNumberAnimations(1);

	mainSprite->setAnimationSpeed(0, 7);
	mainSprite->addKeyframe(0, glm::vec2(0.0f, 0.f));

	mainSprite->changeAnimation(0);

}

void Credits::update(int deltaTime)
{
	// letra m
	
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		backToMenu();
	}
	

	mainSprite->update(deltaTime);
}

void Credits::backToMenu()
{
	Game::instance().changeScene("MENU");
}

void Credits::render()
{
	glm::mat4 modelview;

	texProgram.use();


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	mainSprite->render();

}


void Credits::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

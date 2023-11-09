#include "Menu.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glut.h>


#define SCREEN_X 32
#define SCREEN_Y 16


enum MenuAnims
{
	START, INSTRUCTIONS, CREDITS
};


Menu::Menu()
{

}

Menu::~Menu()
{
	//if (sprite != NULL) delete sprite;
	if (mainSprite != NULL) delete mainSprite;
}


void Menu::init()
{
	initShaders();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);



	spritesheet.loadFromFile("images/menu_bground.png", TEXTURE_PIXEL_FORMAT_RGBA);


	mainSprite = Sprite::createSprite(glm::ivec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)),
		glm::vec2(0.5f, 0.5f), &spritesheet, &texProgram);


	mainSprite->setNumberAnimations(3);

	mainSprite->setAnimationSpeed(START, 7);
	mainSprite->addKeyframe(START, glm::vec2(0.0f, 0.f));
	mainSprite->addKeyframe(START, glm::vec2(0.5f, 0.f));

	mainSprite->setAnimationSpeed(INSTRUCTIONS, 7);
	mainSprite->addKeyframe(INSTRUCTIONS, glm::vec2(0.0f, 0.f));
	mainSprite->addKeyframe(INSTRUCTIONS, glm::vec2(0.f, 0.5f));

	mainSprite->setAnimationSpeed(CREDITS, 7);
	mainSprite->addKeyframe(CREDITS, glm::vec2(0.0f, 0.f));
	mainSprite->addKeyframe(CREDITS, glm::vec2(0.5f, 0.5f));



	mainSprite->changeAnimation(0);
	menuState = START;




}

void Menu::update(int deltaTime)
{


	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (menuState == START)
		{

			menuState = INSTRUCTIONS;
			mainSprite->changeAnimation(INSTRUCTIONS);
		}
		else if (menuState == INSTRUCTIONS)
		{

			menuState = CREDITS;
			mainSprite->changeAnimation(CREDITS);

		}
		Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
		SoundManager::instance().playSound("sounds/change-between-button.wav", 1.f);


	}



	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (menuState == CREDITS)
		{

			menuState = INSTRUCTIONS;
			mainSprite->changeAnimation(INSTRUCTIONS);
		}
		else if (menuState == INSTRUCTIONS)
		{

			menuState = START;
			mainSprite->changeAnimation(START);

		}
		Game::instance().specialKeyReleased(GLUT_KEY_UP);
		SoundManager::instance().playSound("sounds/change-between-button.wav", 1.f);

	}

	// Enter
	if (Game::instance().getKey(13))
	{

		aplyState(menuState);
	}



	mainSprite->update(deltaTime);



}

void Menu::aplyState(int state)
{
	Game::instance().specialKeyReleased(13);

	if (state == 0) Game::instance().changeScene("LEVEL");
	else if (state == 2) Game::instance().changeScene("CREDITS");
	else if (state == 1) Game::instance().changeScene("INSTRUCTIONS");


	menuState = 0;
}

void Menu::render()
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


void Menu::initShaders()
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

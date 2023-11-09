#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.359f, 0.578f, 0.985f, 1.0f);
	activeScene = "MENU";

	if (activeScene == "MENU") menu.init();
	else if (activeScene == "LEVEL") scene.init();
	else if (activeScene == "CREDITS") credits.init();
	else if (activeScene == "INSTRUCTIONS") instructions.init();

}

bool Game::update(int deltaTime)
{

	if (activeScene == "MENU") menu.update(deltaTime);
	else if (activeScene == "LEVEL") scene.update(deltaTime);
	else if (activeScene == "CREDITS") credits.update(deltaTime);
	else if (activeScene == "INSTRUCTIONS") instructions.update(deltaTime);


	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (activeScene == "MENU") menu.render();
	else if (activeScene == "LEVEL") scene.render();
	else if (activeScene == "CREDITS") credits.render();
	else if (activeScene == "INSTRUCTIONS") instructions.render();

}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::changeScene(string id_scene)
{
	activeScene = id_scene;
	if (activeScene == "MENU") menu.init();
	else if (activeScene == "LEVEL") scene.init();
	else if (activeScene == "CREDITS") credits.init();
	else if (activeScene == "INSTRUCTIONS") instructions.init();

}





#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 3
#define INIT_PLAYER_Y_TILES 12


Scene::Scene()
{
	map = NULL;
	player = NULL;
	//goombas = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	for (auto g : enemies) {
		delete g;
	}
	enemies.clear();
	for (auto p : powers) {
		delete p;
	}
	powers.clear();
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/testLevel.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	//enemies.push_back(new Enemy());
	//enemies.push_back(new Enemy());
	//enemies.push_back(new Enemy());
	//enemies.push_back(new Enemy());
	powers.push_back(new Powerup());

	powers[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	powers[0]->setPosition(glm::vec2((INIT_PLAYER_X_TILES) * map->getTileSize(), (INIT_PLAYER_Y_TILES) * map->getTileSize()));
	powers[0]->setTileMap(map);

	int i = 0;
	for (auto enemy : enemies) {
		enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, i%2);
		enemy->setPosition(glm::vec2((6) * map->getTileSize(), (12) * map->getTileSize()));
		enemy->setTileMap(map);
		++i;
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	cameraX = 0.0f;
	paintDamagedMario = true;

	userInterface.init("0", "0", "1-1", "400");
}

void Scene::update(int deltaTime)
{

	if (player->getDone()) {
		if (map != NULL)
			delete map;
		if (player != NULL)
			delete player;
		for (auto g : enemies) {
			delete g;
		}
		enemies.clear();
		for (auto p : powers) {
			delete p;
		}
		powers.clear();
		init();
	}
	currentTime += deltaTime;
	player->update(deltaTime, cameraX-2*map->getTileSize(), enemies);

	if (!player -> getDead()) {
		for (auto enemy : enemies) {
			enemy->update(deltaTime, player->getPosition(), enemies);
		}
		for (auto p : powers) {
			p->update(deltaTime);
		}
	}
}

void Scene::render()
{


	paintDamagedMario = !paintDamagedMario;
	glm::mat4 modelview;

	texProgram.use();

	glm::vec2 posPlayer = player->getPosition();

	if (posPlayer.x - SCREEN_WIDTH / 2 > cameraX)
	{
		cameraX = posPlayer.x - SCREEN_WIDTH / 2;
	}

	projection = glm::ortho(cameraX, cameraX + float(SCREEN_WIDTH - 1),
		float(SCREEN_HEIGHT - 1), 0.f);

	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	if (!player->getInmune() || paintDamagedMario)player->render();
	for (auto enemy : enemies) {
		if (enemy -> getActive())enemy->render();
	}
	for (auto p : powers) {
		if (p->getActive()) p->render();
	}


	userInterface.render();
}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}




#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Powerup.h"
#include <string>
#include "UserInterface.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	std::vector<Enemy*> enemies;
	std::vector<Powerup*> powers;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	float cameraX;
	bool paintDamagedMario;
	UserInterface userInterface;

};


#endif // _SCENE_INCLUDE


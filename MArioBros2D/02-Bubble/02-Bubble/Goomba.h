#ifndef _GOOMBA_INCLUDE
#define _GOOMBA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Goomba is basically a Sprite that represents the goomba enemies. As such it has
// all properties it needs to track its movement, falling, and collisions.


class Goomba
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	bool bJumping, dead;
	glm::ivec2 tileMapDispl, posGoomba;
	int jumpAngle, startY;
	double speed;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _GOOMBA_INCLUDE


#pragma once

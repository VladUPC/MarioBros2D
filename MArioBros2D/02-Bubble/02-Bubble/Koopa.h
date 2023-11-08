#ifndef _KOOPA_INCLUDE
#define _KOOPA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>


// Goomba is basically a Sprite that represents the goomba enemies. As such it has
// all properties it needs to track its movement, falling, and collisions.


class Koopa
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, glm::vec2 posMario, vector<Goomba*> goombas);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	glm::vec2 getPosition();
	glm::vec2 getSize();

private:
	bool bJumping, dead, active;
	glm::ivec2 tileMapDispl, posKoopa, size;
	int jumpAngle, startY;
	double speed;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};


#endif // _KOOPA_INCLUDE


#pragma once
#pragma once

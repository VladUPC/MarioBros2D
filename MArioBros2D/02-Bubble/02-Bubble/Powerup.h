#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>


// Goomba is basically a Sprite that represents the goomba enemies. As such it has
// all properties it needs to track its movement, falling, and collisions.


class Powerup
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int t);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool getActive();

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	glm::vec2 getPosition();
	glm::vec2 getSize();

private:
	bool active, bJumping;
	glm::ivec2 tileMapDispl, pos, size;
	int jumpAngle, startY, type;
	double speed;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

	void mushroomAnim(ShaderProgram& shaderProgram);
	void coinAnim(ShaderProgram& shaderProgram);
	void starAnim(ShaderProgram& shaderProgram);
	void flowerAnim(ShaderProgram& shaderProgram);

};


#endif // _POWERUP_INCLUDE


#pragma once
#pragma once

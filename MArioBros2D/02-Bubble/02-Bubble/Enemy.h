#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>


// Goomba is basically a Sprite that represents the goomba enemies. As such it has
// all properties it needs to track its movement, falling, and collisions.


class Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool t);
	void update(int deltaTime, glm::vec2 posMario, vector<Enemy*> enemys);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	void setDead(bool t);

	bool getActive();

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	glm::vec2 getPosition();
	glm::vec2 getSize();

private:
	bool bJumping, dead, active, type;
	glm::ivec2 tileMapDispl, posEnemy, size;
	int jumpAngle, startY;
	double speed;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	void tortugaAnim(ShaderProgram& shaderProgram);
	void gumbaAnim(ShaderProgram& shaderProgram);
};


#endif // _ENEMY_INCLUDE


#pragma once

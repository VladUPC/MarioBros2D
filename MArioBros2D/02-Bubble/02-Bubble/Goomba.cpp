#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Goomba.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum GoombaAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Goomba::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	//bJumping = false;
	dead = false;
	speed = 2;
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));

}

void Goomba::update(int deltaTime)
{
	sprite->update(deltaTime);

	
	posGoomba.y += FALL_STEP;
	
	map->collisionMoveDown(posGoomba, glm::ivec2(32, 32), &posGoomba.y);

	
	if (speed < 0 && map->collisionMoveLeft(posGoomba, glm::ivec2(32, 32))) speed *= -1;
	if (speed > 0 && map->collisionMoveRight(posGoomba, glm::ivec2(32, 32))) speed *= -1;

	if (speed < 0 && sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
	if (speed > 0 && sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);

	posGoomba.x += speed;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
}

void Goomba::render()
{
	sprite->render();
}

void Goomba::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Goomba::setPosition(const glm::vec2& pos)
{
	posGoomba = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
}





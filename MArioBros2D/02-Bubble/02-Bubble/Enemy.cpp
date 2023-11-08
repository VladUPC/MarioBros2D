#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define Size_X 32
#define Size_Y 32

enum GoombaAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, DIE,
};


void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool t)
{
	type = t;
	active = false;
	dead = false;
	speed = 2;
	if (!t)
	{
		gumbaAnim(shaderProgram);
	}
	else
	{
		tortugaAnim(shaderProgram);	
	}
	

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}


void Enemy::tortugaAnim(ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/tortuga.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//  128 * 92

	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(32.f / 288.f, 46.f / 92.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(STAND_LEFT, 6);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(4 * 32.f / 288.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 6);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(2 * 32.f / 288.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(4 * 32.f / 288.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5 * 32.f / 288.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);

	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2 * 32.f / 288.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 * 32.f / 288.f, 0.f));

	sprite->setAnimationSpeed(DIE, 6);

	sprite->addKeyframe(DIE, glm::vec2(8 * 32.f / 288.f, 0.f));
	sprite->addKeyframe(DIE, glm::vec2(8 * 32.f / 288.f, 46.f / 92.f));


}
void Enemy::gumbaAnim(ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/enemigos_32x32.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//  96 * 96


	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(32.f / 96.f, 32.f / 96.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(32.f / 96.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);

	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(32.f / 96.f, 0.f));

	sprite->setAnimationSpeed(DIE, 8);

	sprite->addKeyframe(DIE, glm::vec2(0.f, 32.f / 96.f));
}

void Enemy::update(int deltaTime, glm::vec2 posMario, vector<Enemy*> Enemys)
{
	
	if (!active) {
		active = (posMario.x - posEnemy.x < 32 && posMario.x < posEnemy.x && !dead);
		//active = false;
	}
	else if (!dead) {
		sprite->update(deltaTime);


		posEnemy.y += FALL_STEP;

		map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y);


		if (speed < 0 && map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32))) speed *= -1;
		if (speed > 0 && map->collisionMoveRight(posEnemy, glm::ivec2(32, 32))) speed *= -1;

		if (speed < 0 && sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
		if (speed > 0 && sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);

		posEnemy.x += speed;

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	}
	for (auto g : Enemys) {
		glm::vec2 gpos = g->getPosition();
		if (speed < 0) {
			if (posEnemy.x > gpos.x && posEnemy.x < gpos.x + Size_X) speed *= -1;
		}
		if (speed > 0) {
			if (posEnemy.x + Size_X > gpos.x && posEnemy.x + Size_X < gpos.x + Size_X) speed *= -1;
		}
	}

	if (Game::instance().getKey(0x0061)) active = false;
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}


glm::vec2 Enemy::getPosition()
{
	return posEnemy;
}

glm::vec2 Enemy::getSize()
{
	return glm::ivec2(32, 32);
}

bool Enemy::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	
	if (pos.x > posEnemy.x && pos.x < (posEnemy.x + Size_X)) {
		if (pos.y > posEnemy.y && pos.y < (posEnemy.y + Size_Y)) return true;
		if (pos.y + size.y > posEnemy.y && pos.y + size.y < (posEnemy.y + Size_Y)) return true;
	}

	return false;
}

bool Enemy::getActive() {
	return active;
}

void Enemy::setDead(bool t) {
	dead = true;
	active = false;
}

/*
bool Enemy::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	if (pos.x < posGoomba.x && pos.x >(posGoomba.x + Size_X)) {
		if (pos.y > posGoomba.y && pos.y < (posGoomba.y + Size_Y)) return true;
		if (pos.y > posGoomba.y && pos.y < (posGoomba.y + Size_Y)) return true;
	}

	return false;
}

bool Goomba::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}
*/



#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Powerup.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define Size_X 32
#define Size_Y 32


enum PowerupAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Powerup::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int t)
{
	type = t;
	active = true;
	speed = 2;
	if (type == 2) speed = 0;
	jumpAngle = 0;
	bJumping = false;

	//mushroomAnim(shaderProgram);
	//coinAnim(shaderProgram);
	flowerAnim(shaderProgram);
	//starAnim(shaderProgram);

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}


void Powerup::update(int deltaTime)
{
	if (type != -1) {
		sprite->update(deltaTime);


		pos.y += FALL_STEP;

		map->collisionMoveDown(pos, glm::ivec2(32, 32), &pos.y);


		if (speed < 0 && map->collisionMoveLeft(pos, glm::ivec2(32, 32))) speed *= -1;
		if (speed > 0 && map->collisionMoveRight(pos, glm::ivec2(32, 32))) speed *= -1;

		/*
		if (speed < 0 && sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
		if (speed > 0 && sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
		*/
		pos.x += speed;

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

		if (type == 1) {
			
			if (bJumping)
			{
				//if (!map -> collisionMoveDown && map -> collission)

				jumpAngle += JUMP_ANGLE_STEP;
				if (jumpAngle == 180)
				{
					bJumping = false;
					pos.y = startY;
				}
				else
				{

					pos.y = int(startY - 100 * sin(3.14159f * jumpAngle / 180.f));
					if (jumpAngle > 90) bJumping = !map->collisionMoveDown(pos, glm::ivec2(32, 32), &pos.y);
				}

			}
			else
			{
				pos.y += FALL_STEP;
				if (map->collisionMoveDown(pos, glm::ivec2(32, 32), &pos.y))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = pos.y;
				}

			}
		}
	}
}

void Powerup::render()
{
	sprite->render();
}

void Powerup::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Powerup::setPosition(const glm::vec2& posi)
{
	pos = posi;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}


glm::vec2 Powerup::getPosition()
{
	return pos;
}

bool Powerup::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{

	if (pos.x > pos.x && pos.x < (pos.x + Size_X)) {
		if (pos.y > pos.y && pos.y < (pos.y + Size_Y)) return true;
		if (pos.y + size.y > pos.y && pos.y + size.y < (pos.y + Size_Y)) return true;
	}

	return false;
}

bool Powerup::getActive() {
	return active;
}



void Powerup::starAnim(ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/items_tile_set.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(16.f / 64.f, 16.f / 128.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 3 * 16.f / 128.f));
}

void Powerup::flowerAnim(ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/items_tile_set.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(16.f / 64.f, 16.f / 128.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 2 * 16.f / 128.f));
}

void Powerup::mushroomAnim(ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/items_tile_set.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(16.f / 64.f, 16.f / 128.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 16.f / 128.f));

}


void Powerup::coinAnim(ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/items_tile_set.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(16.f / 64.f, 16.f / 128.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 6 * 16.f / 128.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 7 * 16.f / 128.f));

}

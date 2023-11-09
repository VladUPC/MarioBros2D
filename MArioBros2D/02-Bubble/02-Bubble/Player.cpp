#include <cmath>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"



#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, 
	JUMP_UP_LEFT, JUMP_DOWN_LEFT, JUMP_UP_RIGHT , JUMP_DOWN_RIGHT,
	DIE, SMALL_TO_BIG_RIGHT, SMALL_TO_BIG_LEFT, BIG_TO_SMALL_LEFT, BIG_TO_SMALL_RIGHT,
	GRAB_FLAG
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	SoundManager::instance().stopAllSounds();
	SoundManager::instance().playSound("sounds/main_theme.wav", 1.f);

	state = "super";
	prevState = state;
	bJumping = false;
	bSprint = false;
	prevJump = false;
	dead = false;
	done = false;
	speed = 0;
	jumpCount = 0;
	maxSpeed = 3;
	prevY = 0;
	inmuneTime = 0;

	size = glm::ivec2(32, 32 );

	marioTipo = 6 * 32.f / 1056.f;

	

	animateMario(marioTipo, size, shaderProgram);

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}
//MARIO DEFAULT  marioTipo = 0.f;
//MARIO ESTRELLA  marioTipo = 30 * 32.f / 1056.f;
//MARIO FUEGO  marioTipo = 6 * 32.f / 1056.f;
void Player::animateMario(int type, glm::ivec2 size, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/mario_move.png", TEXTURE_PIXEL_FORMAT_RGBA);


	sprite = Sprite::createSprite(size, glm::vec2(32.f / 1344.f, 2 * 32.f / 1056.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(14);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(20 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(21 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(20 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(19 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(18 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(17 * 32.f / 1344.f, marioTipo));


	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(21 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(22 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(23 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(34 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(JUMP_UP_RIGHT, 8);
	sprite->addKeyframe(JUMP_UP_RIGHT, glm::vec2(26 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(JUMP_DOWN_RIGHT, 8);
	sprite->addKeyframe(JUMP_DOWN_RIGHT, glm::vec2(28 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(JUMP_UP_LEFT, 8);
	sprite->addKeyframe(JUMP_UP_LEFT, glm::vec2(15 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(JUMP_DOWN_LEFT, 8);
	sprite->addKeyframe(JUMP_DOWN_LEFT, glm::vec2(13 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(DIE, 8);
	sprite->addKeyframe(DIE, glm::vec2(5 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(SMALL_TO_BIG_RIGHT, 2);
	sprite->addKeyframe(SMALL_TO_BIG_RIGHT, glm::vec2(36 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(SMALL_TO_BIG_RIGHT, glm::vec2(37 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(SMALL_TO_BIG_LEFT, 2);
	sprite->addKeyframe(SMALL_TO_BIG_LEFT, glm::vec2(5 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(SMALL_TO_BIG_LEFT, glm::vec2(4 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(BIG_TO_SMALL_RIGHT, 2);
	sprite->addKeyframe(BIG_TO_SMALL_RIGHT, glm::vec2(21 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(BIG_TO_SMALL_RIGHT, glm::vec2(36 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(BIG_TO_SMALL_LEFT, 2);
	sprite->addKeyframe(BIG_TO_SMALL_LEFT, glm::vec2(20 * 32.f / 1344.f, marioTipo));
	sprite->addKeyframe(BIG_TO_SMALL_LEFT, glm::vec2(5 * 32.f / 1344.f, marioTipo));

	sprite->setAnimationSpeed(GRAB_FLAG, 2);
	sprite->addKeyframe(GRAB_FLAG, glm::vec2(29 * 32.f / 1344.f, marioTipo));

	
}


void Player::update(int deltaTime, float camPosX, vector<Enemy*> enemies)
{
	done = posPlayer.y > 640;
	if (!dead) {
		if (inmuneTime > 0) inmuneTime -= deltaTime;
		if (inmuneTime < 0) inmuneTime = 0;
		sprite->update(deltaTime);
		prevY = posPlayer.y;
		if (bJumping)
		{
			//if (!map -> collisionMoveDown && map -> collission)

			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) jumpCount++;
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{

				posPlayer.y = int(startY - 96 / 2 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpCount == 19) {
					startY = posPlayer.y;
					jumpAngle = 0;
				}
				if (jumpCount >= 20) {
					posPlayer.y = int(startY - 96 / 2 * sin(3.14159f * jumpAngle / 180.f));
					prevJump = false;
				}
				if (jumpAngle > 90) bJumping = !map->collisionMoveDown(posPlayer, size, &posPlayer.y);
			}
			prevJump = Game::instance().getSpecialKey(GLUT_KEY_UP);

		}
		else
		{
			posPlayer.y += FALL_STEP;
			jumpCount = 0;
			if (map->collisionMoveDown(posPlayer, size, &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP) || Game::instance().getKey(0x0020))
				{

					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
					jumpCount++;
					SoundManager::instance().playSound("sounds/jump_mario.wav", 2.f);

				}
				bSprint = Game::instance().getSpecialKey(0x0070);
			}

		}



		if (bSprint) maxSpeed = 5.75;
		else maxSpeed = 1.5;
		if (speed < -maxSpeed) speed += 0.5;
		if (speed > maxSpeed) speed -= 0.5;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if (speed <= 0) {
				if (abs(speed) < maxSpeed) speed -= 0.2;
			}
			else {
				speed -= 0.2;
			}

		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			if (speed >= 0) {
				if (abs(speed) < maxSpeed + 0.5) speed += 0.5;
			}
			else {
				speed += 0.2;
			}

		}
		else {
			if (speed > 0) {
				if (speed - 0.15 < 0) speed = 0;
				else speed -= 0.15;
			}
			else if (speed < 0) {
				if (speed + 0.15 > 0) speed = 0;
				else speed += 0.15;
			}
		}

		if (speed < 0 && map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32))) speed = 0;
		if (speed > 0 && map->collisionMoveRight(posPlayer, glm::ivec2(32, 32))) speed = 0;

		if (speed < 0 && sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
		if (speed > 0 && sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
		if (speed == 0) {
			if (sprite->animation() == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
			if (sprite->animation() == MOVE_RIGHT) sprite->changeAnimation(STAND_RIGHT);
		}

		posPlayer.x += speed;

		if (posPlayer.x < camPosX) {
			posPlayer.x = camPosX;
			speed = 0;
		}

		for (auto g : enemies) {
			if (g->getActive()) {
				if (g->getActive() && checkColisionDown(g->getPosition(), g->getSize())) {
					g->setDead(state == "star");
					bJumping = true;
					startY = posPlayer.y;
					jumpAngle = 0;
				}
				else if (inmuneTime == 0 && checkOtherCollisions(g->getPosition(), g->getSize())) {
					if (state == "star") g->setDead(true);
					else {
						if (state != "default") {
							state = "default";
							inmuneTime = 5000;
						}
						else 
						{
							SoundManager::instance().stopAllSounds();
							SoundManager::instance().playSound("sounds/mariodie.wav", 1.f);
							dead = true;
						}
					}
				}
			}
		}

		//for (auto p : pow)
	}
	else {
		if (!bJumping && jumpAngle != 180) {
			bJumping = true;
			startY = posPlayer.y;
			jumpAngle = 0;
		}
		else {
			if (jumpAngle == 180)
			{
				posPlayer.y += 4;
			}
			else
			{
				jumpAngle += JUMP_ANGLE_STEP;
				posPlayer.y = int(startY - 96 / 2 * sin(3.14159f * jumpAngle / 180.f));
			}
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}


void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	if (state =="super" || state == "fire") posPlayer.y -= 32;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}






bool Player::checkColisionDown(const glm::vec2& pos, const glm::vec2& sizeE) {
	if ((posPlayer.x > pos.x && posPlayer.x < pos.x + sizeE.x) || (posPlayer.x + size.x > pos.x && posPlayer.x + size.x < pos.x + size.x)) {
		if (posPlayer.y + size.y > pos.y && posPlayer.y +size.y < pos.y + sizeE.y) return prevY < posPlayer.y;
	}
	return false;
}

bool Player::checkOtherCollisions(const glm::vec2& pos, const glm::vec2& sizeE) {
	if ((posPlayer.x > pos.x && posPlayer.x < pos.x + sizeE.x) || (posPlayer.x + size.x > pos.x && posPlayer.x + size.x < pos.x + size.x)) {
		if (posPlayer.y + size.y >= pos.y && posPlayer.y + size.y <= pos.y + sizeE.y && prevY >= posPlayer.y) return true;
		if (posPlayer.y >= pos.y && posPlayer.y <= pos.y + sizeE.y) return true;
	}
	return false;
}

bool Player::getInmune() {
	return inmuneTime > 0 && state != "star";
}

bool Player::getDead() {
	return dead;
}

bool Player::getDone() {
	return done;
}





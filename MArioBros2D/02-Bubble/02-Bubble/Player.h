#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"
#include "SoundManager.h"



// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, float camPosX, vector<Enemy*> enemies);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 Player::getPosition();
	
	bool checkColisionDown(const glm::vec2& pos, const glm::vec2& size);
	bool checkOtherCollisions(const glm::vec2& pos, const glm::vec2& size);
	bool getInmune();
	bool getDead();
	bool getDone();
	
private:
	bool bJumping, bSprint, prevJump, dead, done;
	glm::ivec2 tileMapDispl, posPlayer, size;
	int jumpAngle, startY, jumpCount, prevY, inmuneTime;
	double speed, maxSpeed;
	double marioTipo;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	string state, prevState;

	void animateMario(int type, glm::ivec2 size, ShaderProgram& shaderProgram);

};


#endif // _PLAYER_INCLUDE



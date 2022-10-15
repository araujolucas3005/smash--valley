#ifndef _SVW_PLAYER_H_
#define _SVW_PLAYER_H_

#include "Types.h"                      
#include "Object.h"                     
#include "Sprite.h"                    
#include "Image.h"
#include "Scene.h"
#include "Platform.h"
#include "Timer.h"
#include "string"
#include "Character.h"
#include "Audio.h"
#include <vector>
using namespace std;

enum PLAYERSTATE { LEFT, RIGHT };
enum PLAYERID { ONE, TWO };

struct MovementKeys {
	int up;
	int left;
	int down;
	int right;
	int jump;
	int attack;
	int dash;
};

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	uint prevState = STILL;
	uint state = STILL;
	PLAYERID id;

	float prevX, prevY;
	float velX, velY, prevVelY, beforeHitVelX, beforeHitVelY;
	float width, height;

	bool ctrlJump, ctrlAttack, ctrlDown, ctrlDash, stoppedAfterHit, invulnerableFromHit;

	uint rebornDirection;

	float gravity = 1;
	ushort jumps = 0;

	Timer* dashingTimer = nullptr;
	Timer* stopAfterHitTimer = nullptr;
	Timer* hitInvunerabilityTimer = nullptr;

	Geometry* attackRect;
	Geometry* attackRightRect;
	Geometry* currAttackRect;

	void PlatformCollision(Platform* platform);
	void TraversablePlatformCollision(Platform* platform);
	void PlayerCollision(Player* enemy);

public:
	//n�o deletar no player, vai ser deletado no game principal
	Character* character = nullptr;

	MovementKeys mk;

	bool isAttacking, isFlyingFromHit, isDashing, isReborning = false;
	float hits = 2;
	int life = 5;
	float percentToThrow = 0;

	Timer* attackTimer = nullptr;
	Timer* hitFlyingTimer = nullptr;
	Timer* rebornTimer = nullptr;
	Timer* levelEndingTimer = nullptr;
	Timer* enemyInvunerabilityTimer = nullptr;
	Timer* attackDelayTimer = nullptr;

	uint lookingDir = RIGHT;

	Player(MovementKeys mk, PLAYERID id, uint rebornDirection);
	~Player();                          // destrutor

	void Stop();                        // p�ra jogador
	void Up();                          // muda dire��o para cima
	void Down();                        // muda dire��o para baixo
	void Left();                        // muda dire��o para esquerda
	void Right();                       // muda dire��o para direita
	void WhenHit(Player* player);
	void Reset();
	void ResetAfterLevel();

	void OnCollision(Object* obj);     // resolu��o da colis�o

	void Update();                      // atualiza��o do objeto
	void Draw();                        // desenho do objeto
};

#endif
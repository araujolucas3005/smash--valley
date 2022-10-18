/**********************************************************************************
// Player (C�digo Fonte)
//
// Cria��o:     01 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Player do jogo SVW
//
**********************************************************************************/

#include "GameTest.h"
#include "Player.h"
#include "Platform.h"
#include "SmashDragon.h"
#include "Level.h"
#include "LevelAnim.h"
#include <random>

// ---------------------------------------------------------------------------------

Player::Player(MovementKeys mk, PLAYERID id, uint rebornDirection) : mk(mk), id(id), rebornDirection(rebornDirection)
{
	if (id == ONE) lookingDir == LEFT;
	else lookingDir = RIGHT;

	type = PLAYER;

	Mixed* mixed = new Mixed();

	mixed->Insert(new Rect(-15, -25, 15, 80));
	mixed->Insert(new Rect(-30, -25, 30, 80));

	attackRect = new Rect(-60, -10, 20, 5);
	attackRightRect = new Rect(-20, -10, 60, 5);
	currAttackRect = attackRect;

	attackRight = new Attack();
	attackLeft = new Attack();

	attackRight->BBox(new Rect(-20, -10, 60, 5));
	attackLeft->BBox(new Rect(-60, -10, 20, 5));

	BBox(mixed);

	height = 160; width = 60;
	prevX = x;  prevY = y;
	prevVelY = velY = velX = beforeHitVelX = beforeHitVelY = 0;
	prevVelY = velY = velX = 0;

	ctrlJump = ctrlAttack = ctrlDown = ctrlDash = true;
	isAttacking = isFlyingFromHit = isDashing = stoppedAfterHit = invulnerableFromHit = isReborning = false;

	jumpEffect = new TileSet("Resources/jump_straight_sprite.png", 100, 100, 6, 6);
	jumpAnim = new Animation(jumpEffect, 0.0180f, false);

	hitEffectR = new TileSet("Resources/strong_hit_sprite_small_r.png", 240, 240, 4, 4);
	hitAnimR = new Animation(hitEffectR, 0.0120f, false);

	hitEffectL = new TileSet("Resources/strong_hit_sprite_small_l.png", 240, 240, 4, 4);
	hitAnimL = new Animation(hitEffectL, 0.0120f, false);
	uint seq[] = { 3, 2, 1, 0 };
	hitAnimL->Add(1, seq, 4);
	hitAnimL->Select(1);

	attackTimer = new Timer();
	hitFlyingTimer = new Timer();
	dashingTimer = new Timer();
	rebornTimer = new Timer();
	stopAfterHitTimer = new Timer();
	hitInvunerabilityTimer = new Timer();
	levelEndingTimer = new Timer();
	attackDelayTimer = new Timer();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete attackTimer;
	delete hitFlyingTimer;
	delete dashingTimer;
	delete rebornTimer;
	delete stopAfterHitTimer;
	delete hitInvunerabilityTimer;
	delete levelEndingTimer;
	delete attackDelayTimer;
	delete attackRect;
	delete attackRightRect;
	delete attackRight;
	delete attackLeft;
	delete jumpEffect;
	delete jumpAnim;
	delete hitAnimR;
	delete hitAnimL;
	delete hitEffectR;
	delete hitEffectL;
}

// ---------------------------------------------------------------------------------

void Player::Stop()
{
	velX = 0;
	velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Up()
{
	velY = -300.0f;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
	velY = 300.0f;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
	lookingDir = LEFT;

	if (!isDashing)
		velX = -300.0f;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
	lookingDir = RIGHT;

	if (!isDashing)
		velX = 300.0f;
}

void Player::WhenHit(Player* enemy)
{
	if (enemy->prevVelY == 0 && enemy->velX == 0)
	{
		velX = (enemy->lookingDir == RIGHT ? 300 : -300) * (hits / 6.0f);
	}
	else
	{
		velX = enemy->velX * (hits / 6.0f);
	}

	velY = (enemy->velY < 0 ? -1 : 1) * 200 * (hits / 1.5f);

	beforeHitVelX = velX;
	beforeHitVelY = velY;

	hits++;

	int number = rand() % 1;

	if (number == 0)
		SmashDragon::audio->Play(PUNCH1, false);
	else
		SmashDragon::audio->Play(PUNCH2, false);

	if (enemy->lookingDir == RIGHT)
	{
		if (hitAnimR->Inactive())
			hitAnimR->Restart();
		hitDirection = RIGHT;
		xHit = enemy->X() + (enemy->width / 2);
	}
	else
	{
		if (hitAnimL->Inactive())
			hitAnimL->Restart();
		hitDirection = LEFT;
		xHit = enemy->X() - (enemy->width / 2);
	}

	yHit = enemy->Y();

	percentToThrow = (hits - 1) * 13.55;

	isFlyingFromHit = true;
	hitFlyingTimer->Start();

	stoppedAfterHit = true;
	stopAfterHitTimer->Start();

	enemy->stoppedAfterHit = true;
	enemy->stopAfterHitTimer->Start();

	invulnerableFromHit = true;
	hitInvunerabilityTimer->Start();

	lookingDir = enemy->lookingDir == RIGHT ? LEFT : RIGHT;
}

void Player::PlatformCollision(Platform* platform)
{
	gravity = 1;

	if (!isFlyingFromHit)
	{
		bool jump = false;

		if (platform->Y() + platform->height / 2 < prevY - 20)
		{
			velY = 0;

			MoveTo(x, prevY);
		}
		else if (platform->Y() - platform->height / 2 < prevY + height / 2)
		{
			velX = 0;

			if (x < platform->Width())
			{
				MoveTo(platform->X() - platform->width / 2 - width / 2 - 2, y);
			}
			else
			{
				MoveTo(platform->X() + platform->width / 2 + width / 2 + 2, y);
			}
		}
		else
		{
			if (!isDashing)
			{
				jumps = velX = 0;
			}


			velY = 0;

			MoveTo(x, platform->Y() - platform->height / 2 - height / 2);
		}
	}
	else
	{
		MoveTo(x, platform->Y() - platform->height / 2 - height / 2);

		velY = -velY / 1.5;

	}
}

void Player::TraversablePlatformCollision(Platform* platform)
{
	if (velY >= 0 && prevY + height / 2 <= platform->Y() - platform->Height() / 2)
	{
		gravity = 1;

		if (!isFlyingFromHit)
		{

			if (window->KeyDown(mk.down))
			{
				MoveTo(x, y + 1.0f);
			}
			else if (window->KeyDown(mk.jump))
			{
				MoveTo(x, y - 1.0f);
			}
			else
			{
				if (!isDashing)
				{
					jumps = velX = 0;
				}

				velY = 0;

				MoveTo(x, platform->Y() - platform->height / 2 - height / 2);
			}
		}
		else
		{
			MoveTo(x, platform->Y() - platform->height / 2 - height / 2);

			velY = -velY / 1.5;
		}
	}
}

void Player::PlayerCollision(Player* enemy)
{
	if (enemy == this) return;

	bool attackCollision = false;

	if (enemy->isAttacking && !invulnerableFromHit)
	{
		Level* level = (Level*)SmashDragon::level;

		if (enemy->lookingDir == RIGHT)
		{
			attackCollision = level->scene->Collision(enemy->attackRight, this);
		}
		else
		{
			attackCollision = level->scene->Collision(enemy->attackLeft, this);
		}

		if (!isDashing && attackCollision)
		{


			WhenHit(enemy);
		}
	}
	else if (isAttacking && !enemy->invulnerableFromHit)
	{
		Level* level = (Level*)SmashDragon::level;

		if (lookingDir == RIGHT)
		{
			attackCollision = level->scene->Collision(attackRight, enemy);
		}
		else
		{
			attackCollision = level->scene->Collision(attackLeft, enemy);
		}

		if (!enemy->isDashing && attackCollision)
		{
			/*		LevelAnim* dashAnim = new LevelAnim(SmashDragon::hit, 0.100f, false);
					dashAnim->MoveTo(x, y);
					Level* level = (Level*)SmashDragon::level;
					level->scene->Add(dashAnim, STATIC);*/


			enemy->WhenHit(this);
		}
	}
}

void Player::Reset()
{

	if (id == ONE) lookingDir = RIGHT;
	else lookingDir = LEFT;

	state = STILL;
	velY = 100;
	prevX = x;  prevY = y;
	prevVelY = velY;
	velX = 0;
	beforeHitVelX = velX;
	beforeHitVelY = velY;
	gravity = 1;
	hits = 2;
	jumps = 0;
	percentToThrow = 0;

	ctrlJump = ctrlAttack = ctrlDown = ctrlDash = true;
	isAttacking = isFlyingFromHit = isDashing = stoppedAfterHit = invulnerableFromHit = false;

	attackTimer->Reset();
	hitFlyingTimer->Reset();
	dashingTimer->Reset();
	rebornTimer->Reset();
	stopAfterHitTimer->Reset();
	hitInvunerabilityTimer->Reset();
}

void Player::ResetAfterLevel()
{
	Reset();
	lost = false;
	life = 3;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == PLATFORM)
	{
		Platform* platform = (Platform*)obj;

		PlatformCollision(platform);
	}
	else if (obj->Type() == TRAVERSABLE_PLATFORM)
	{
		Platform* platform = (Platform*)obj;

		TraversablePlatformCollision(platform);
	}
	else if (obj->Type() == PLAYER)
	{
		Player* enemy = (Player*)obj;

		PlayerCollision(enemy);
	}
}


// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (SmashDragon::passLevel)
	{
		if (isAttacking)
		{
			isAttacking = false;

			Mixed* geo = (Mixed*)BBox();
			geo->Remove(currAttackRect);
		}
		if (!lost)
		{
			lookingDir = LEFT;
			character->anim->Delay(0.1f);
			character->anim->Select(WINNEREND);
			character->anim->NextFrame();
		}
	}
	else
	{
		attackRect->MoveTo(x, y);
		attackRightRect->MoveTo(x, y);

		attackRight->MoveTo(x, y);
		attackLeft->MoveTo(x, y);

		character->anim->Delay(0.1f);
		character->animRight->Delay(0.1f);

		prevX = x; prevY = y; prevVelY = velY;

		prevState = state;

		if (velY > 0)
		{
			state = JUMPDOWN;
		}
		else if (velY < 0)
		{
			state = JUMPUP;
		}

		if (stoppedAfterHit)
		{
			velX = velX * 0.1;
			velY = velY * 0.1;
		}
		else if (!isReborning)
		{
			if (isFlyingFromHit)
			{
				if (velX > 0)
				{
					velX -= 0.25;
				}
				else if (velX < 0)
				{
					velX += 0.25;
				}
			}
			else
			{
				if (window->KeyDown(mk.jump) && ctrlJump && jumps < 4)
				{
					MoveTo(x, y - 1.0f);

					velY = -500;

					gravity = 1;

					jumps++;

					ctrlJump = false;

					SmashDragon::audio->Play(JUMP, false);

					if (jumpAnim->Inactive())
						jumpAnim->Restart();
					xJump = x;
					yJump = y + ((height - 20) / 2);
				}

				else if (window->KeyUp(mk.jump))
				{
					ctrlJump = true;
				}

				if (!isDashing)
				{
					if (window->KeyDown(mk.attack) && ctrlAttack && !isAttacking && attackDelayTimer->Elapsed(1.0f))
					{
						Mixed* geo = (Mixed*)BBox();

						if (lookingDir == RIGHT)
						{
							geo->Insert(attackRightRect);
							currAttackRect = attackRightRect;
						}
						else
						{
							geo->Insert(attackRect);
							currAttackRect = attackRect;
						}

						attackDelayTimer->Start();

						state = HIT;

						ctrlAttack = false;

						isAttacking = true;

						attackTimer->Start();

						character->anim->Restart();
						character->animRight->Restart();
					}
					else if (window->KeyUp(mk.attack))
					{
						ctrlAttack = true;
					}

					if (window->KeyDown(mk.left))
					{
						if (prevVelY == 0)
							state = WALKLEFT;

						Left();
					}

					if (window->KeyDown(mk.right))
					{
						if (prevVelY == 0)
							state = WALKLEFT;

						Right();
					}

					if (window->KeyDown(mk.down) && ctrlDown)
					{
						ctrlDown = false;

						gravity = 3;
					}
					else if (window->KeyUp(mk.down))
					{
						ctrlDown = true;
					}

					if (window->KeyDown(mk.dash) && ctrlDash && dashingTimer->Elapsed() > 2.0f)
					{


						ctrlDash = isDashing = true;

						dashingTimer->Start();

						velX = lookingDir == RIGHT ? 400 : -400;

						velY = 0;

						gravity = 0;
					}
					else if (window->KeyUp(mk.dash))
					{
						ctrlDash = true;
					}
				}
			}
		}

		velY += gravity * gameTime * 1000;

		Translate(velX * gameTime, velY * gameTime);

		if (isFlyingFromHit)
		{
			state = HITTAKEN;

			if (hitFlyingTimer->Elapsed() > 0.25 * (hits / 3.0f))
			{
				isFlyingFromHit = false;
			}
		}

		if (isReborning)
		{
			if (rebornTimer->Elapsed() > 0.5f)
			{
				isReborning = false;
			}
		}

		if (isDashing)
		{
			state = DASH;

			if (dashingTimer->Elapsed() > 0.4f)
			{
				isDashing = false;

				gravity = 1;
			}
		}

		if (isAttacking)
		{
			if (velX == 0 && prevVelY == 0)
			{
				character->anim->Delay(0.032f);
				character->animRight->Delay(0.032f);
				state = HIT;
			}

			else
			{
				character->anim->Delay(0.032f);
				character->animRight->Delay(0.032f);
				state = MOVINGATTACK;
			}


			if (attackTimer->Elapsed() > 0.2f)
			{
				isAttacking = false;

					Mixed* geo = (Mixed*)BBox();
					geo->Remove(currAttackRect);
			}
		}

		if (stoppedAfterHit) {
			if (stopAfterHitTimer->Elapsed() > 0.2f)
			{
				if (invulnerableFromHit)
				{
					velX = beforeHitVelX;
					velY = beforeHitVelY;
				}


				stoppedAfterHit = false;
			}
		}

		if (invulnerableFromHit) {
			if (hitInvunerabilityTimer->Elapsed(0.8f))
			{
				invulnerableFromHit = false;
			}
		}

		if (velX == 0 && prevVelY == 0 && !isAttacking)
		{
			state = STILL;
		}

		else if ((x - 40 > window->Width()) || (x + 40 < 0) || (Y() - 90 > window->Height()))
		{
			SmashDragon::audio->Play(OUTOFSCREEN, false);
			gravity = 1;
			life--;
			velY = 100.0f;
			velX = 0.0f;
			hits = 2;
			isReborning = true;
			rebornTimer->Start();


			if (life <= 0)
			{
				if (id == ONE)
					SmashDragon::playerOnePoints -= 1;
				else
					SmashDragon::playerTwoPoints -= 1;

				lost = true;
				SmashDragon::passLevel = true;
			}
			else
			{

				if (id == ONE)
				{
					lookingDir = RIGHT;
					MoveTo(200.0f, 0);
				}
				else
				{
					lookingDir = LEFT;
					MoveTo(window->Width() - 200.0f, 0);
				}
			}
		}

		if (!stoppedAfterHit)
		{
			if (lookingDir == RIGHT)
			{
				if (state == STILL && character->animRight->Inactive())
				{
					character->animRight->Restart();
				}
				else
				{
					character->animRight->Select(state);
					character->animRight->NextFrame();
				}

			}
			else
			{

				if (state == STILL && character->anim->Inactive())
				{
					character->anim->Restart();
				}
				else
				{

					character->anim->Select(state);
					character->anim->NextFrame();
				}

			}
		}
	}

	jumpAnim->NextFrame();
	hitAnimL->NextFrame();
	hitAnimR->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
	if (lookingDir == RIGHT)
	{
		character->animRight->Draw(x, y, z, 1.0f, 0.0f, { 1, hits > 8 ? 6 / (hits + 4) : 1, 1, 1 });
	}
	else
	{
		character->anim->Draw(x, y, z, 1.0f, 0.0f, { 1, hits > 8 ? 6 / (hits + 4) : 1, 1, 1 });
	}

	if (state == JUMPUP)
		jumpAnim->Draw(xJump, yJump, z);

	if (state == HITTAKEN)
		if (hitDirection == RIGHT)
			hitAnimR->Draw(xHit, yHit, z);
		else
			hitAnimL->Draw(xHit, yHit, z);
}
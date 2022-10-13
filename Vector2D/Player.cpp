/**********************************************************************************
// Player (Código Fonte)
//
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo SVW
//
**********************************************************************************/

#include "GameTest.h"
#include "Player.h"
#include "Platform.h"
#include <random>

// ---------------------------------------------------------------------------------

Player::Player(MovementKeys mk) : mk(mk)
{
	type = PLAYER;

	BBox(new Rect(-20, -30, 20, 30));

	height = 60; width = 40;
	prevX = x;  prevY = y;
	prevVelY = velY = velX = 0;

	ctrlJump = ctrlAttack = ctrlDown = ctrlDash = true;
	isAttacking = isFlyingFromHit = isDashing = false;

	attackTimer = new Timer();
	hitFlyingTimer = new Timer();
	dashingTimer = new Timer();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete attackTimer;
	delete hitFlyingTimer;
	delete dashingTimer;
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
	enemy->isAttacking = true;

	enemy->attackTimer->Start();

	if (enemy->prevVelY == 0 && enemy->velX == 0)
	{
		velX = (enemy->lookingDir == RIGHT ? 300 : -300) * (hits / 6.0f);
	}
	else
	{
		velX = enemy->velX * (hits / 6.0f);
	}

	velY = (enemy->velY < 0 ? -1 : 1) * 200 * (hits / 2.5f);

	isFlyingFromHit = true;

	hits++;

	hitFlyingTimer->Start();
}

void Player::PlatformCollision(Platform* platform)
{
	gravity = 1;

	if (!isFlyingFromHit)
	{
		bool jump = false;

		if (window->KeyDown(mk.jump))
		{
			MoveTo(x, y - 1.0f);

			jump = true;
		}

		if (platform->Y() + platform->height / 2 < prevY - height / 2)
		{
			velY = 0;

			MoveTo(x, platform->Y() + platform->height / 2 + height / 2 + 2);
		}
		else if (platform->Y() - platform->height / 2 < prevY + height / 2)
		{
			velX = 0;

			if (x < platform->X())
			{
				MoveTo(platform->X() - platform->width / 2 - width / 2 - 2, y);
			}
			else
			{
				MoveTo(platform->X() + platform->width / 2 + width / 2 + 2, y);
			}
		}
		else if (!jump)
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
	if (velY > 0 && prevY + height / 2 <= platform->Y() - platform->Height() / 2)
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
				jumps = velX = velY = 0;

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
	if (window->KeyDown(mk.attack) && ctrlAttack && !isAttacking && !isDashing)
	{
		ctrlAttack = false;

		if (enemy->isAttacking)
		{
			if (!isDashing)
			{
				WhenHit(enemy);
			}
		}
		else
		{
			if (!enemy->isDashing)
			{
				enemy->WhenHit(this);
			}
		}
	}
	else if (window->KeyUp(mk.attack))
	{
		ctrlAttack = true;
	}
}

void Player::Reset() 
{
	height = 60; width = 40;
	prevX = x;  prevY = y;
	prevVelY = velY = velX = 0;
	gravity = 1;

	ctrlJump = ctrlAttack = ctrlDown = ctrlDash = true;
	isAttacking = isFlyingFromHit = isDashing = false;

	attackTimer->Reset();
	hitFlyingTimer->Reset();
	dashingTimer->Reset();
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
	prevX = x;  prevY = y; prevVelY = velY;

	if (isFlyingFromHit)
	{
		if (hitFlyingTimer->Elapsed() > 0.25 * (hits / 3.0f))
		{
			isFlyingFromHit = false;
		}
		else if (velX > 0)
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
			velY = -500;

			gravity = 1;

			jumps++;

			ctrlJump = false;
		}
		else if (window->KeyUp(mk.jump))
		{
			ctrlJump = true;
		}

		if (!isDashing)
		{
			if (window->KeyDown(mk.left))
			{
				Left();
			}

			if (window->KeyDown(mk.right))
			{
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

	if (isDashing)
	{
		if (dashingTimer->Elapsed() > 0.25f)
		{
			isDashing = false;

			gravity = 1;
		}
	}

	if (isAttacking)
	{
		if (attackTimer->Elapsed() > 0.25f)
		{
			isAttacking = false;
		}
	}

	velY += gravity * gameTime * 1000;

	Translate(velX * gameTime, velY * gameTime);

	if (x + 20 < 0)
		MoveTo(window->Width() + 20.f, Y());

	if (x - 20 > window->Width())
		MoveTo(-20.0f, Y());

	if (Y() + 20 < 0)
		MoveTo(x, window->Height() + 20.0f);

	if (Y() - 20 > window->Height())
		MoveTo(x, -20.0f);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
	
}
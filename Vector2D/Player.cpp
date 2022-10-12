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
enum { MUSIC, EFFECT, FOODSOUND, DEATH, PROJECTILESOUND };

// ---------------------------------------------------------------------------------

Player::Player(MovementKeys movementKeys)
{
	type = PLAYER;

	this->movementKeys = movementKeys;

	BBox(new Rect(-20, -30, 20, 30));
	type = PLAYER;

	height = 60;
	width = 40;
	yUp = 0;
	prevX = x;
	prevY = y;
	prevVelY = velY;

	jumpTimer = new Timer();
	attackTimer = new Timer();
	hitTimer = new Timer();
	hitFlyingTimer = new Timer();
	dashingTimer = new Timer();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete spriteL;
	delete spriteR;
	delete spriteU;
	delete spriteD;
	delete jumpTimer;
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

	OutputDebugString(std::to_string(prevVelY).c_str());
	OutputDebugString(" - ");
	OutputDebugString(std::to_string(enemy->prevVelY).c_str());
	OutputDebugString("\n");

	if (enemy->prevVelY == 0 && enemy->velX == 0)
	{
		velX = (enemy->lookingDir == RIGHT ? 200 : -200) * (hits / 6.0f);
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

		if (window->KeyDown(movementKeys.jump))
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
	//OutputDebugString(std::to_string(prevY).c_str());
	//OutputDebugString(" - ");
	//OutputDebugString(std::to_string(y).c_str());
	//OutputDebugString("\n");

	if (velY > 0 && prevY + height / 2 <= platform->Y() - platform->Height() / 2)
	{
		gravity = 1;

		if (!isFlyingFromHit)
		{
			if (window->KeyDown(movementKeys.down))
			{
				MoveTo(x, y + 1.0f);
			}
			else if (window->KeyDown(movementKeys.jump))
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
	if (window->KeyDown(movementKeys.attack) && ctrlAttack && !isAttacking && !isDashing)
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
	else if (window->KeyUp(movementKeys.attack))
	{
		ctrlAttack = true;
	}
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
	prevX = x;
	prevY = y;
	prevVelY = velY;

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
		if (window->KeyDown(movementKeys.jump) && ctrlJump && jumps < 4)
		{
			velY = -500;

			gravity = 1;

			jumps++;

			ctrlJump = false;
		}
		else if (window->KeyUp(movementKeys.jump))
		{
			ctrlJump = true;
		}

		if (!isDashing)
		{
			if (window->KeyDown(movementKeys.left))
			{
				Left();
			}

			if (window->KeyDown(movementKeys.right))
			{
				Right();
			}

			if (window->KeyDown(movementKeys.up))
			{
				lookingDir = UP;
			}

			if (window->KeyDown(movementKeys.down) && ctrlDown)
			{
				ctrlDown = false;

				gravity = 3;
			}
			else if (window->KeyUp(movementKeys.down))
			{
				ctrlDown = true;
			}

			if (window->KeyDown(movementKeys.dash) && ctrlDash && dashingTimer->Elapsed() > 2.0f)
			{
				ctrlDash = false;

				isDashing = true;

				dashingTimer->Start();

				velX = lookingDir == RIGHT ? 400 : -400;

				velY = 0;

				gravity = 0;
			}
			else if (window->KeyUp(movementKeys.dash))
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

	/*OutputDebugString(std::to_string(gameTime).c_str());
	OutputDebugString("\n");*/

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
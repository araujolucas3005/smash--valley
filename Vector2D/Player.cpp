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

	BBox(new Rect(-20, -45, 20, 45));
	type = PLAYER;

	height = 90;
	width = 40;

	jumpTimer = new Timer();
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
	velX = -300.0f;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
	velX = 300.0f;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == PLATFORM) {
		Platform* platform = (Platform*)obj;

		if (onAir && platform->Y() - platform->height / 2 + 5 < Y() + height / 2) {
			if (x < platform->X()) {
				MoveTo(platform->X() - platform->width / 2 - width / 2 - 1, y);
			}
			else {
				MoveTo(platform->X() + platform->width / 2 + width / 2 + 1, y);
			}
		}
		else {

			velY = 0;
			onAir = false;
			jumps = 0;

			if (window->KeyDown(movementKeys.jump)) {
				jumps++;
				MoveTo(x, y - 1.0f);
			}
			else {
				MoveTo(x, platform->Y() - platform->height / 2 - height / 2);
			}
		}


	}
}


// ---------------------------------------------------------------------------------

void Player::Update()
{
	// tá caindo
	if (velY > 0) {
		onAir = true;
	}

	if (window->KeyDown(movementKeys.jump) && ctrlJump && onAir && jumps < 4) {
		jumps++;

		ctrlJump = false;

		jumpTimer->Start();

		velY = -100.0f;
	}
	else if (window->KeyUp(movementKeys.jump)) {
		ctrlJump = true;
	}
	
	// caindo
	if (jumpTimer->Elapsed() > 0.18f) {
		velY += 500.0f * gameTime * 3;
	}

	// subindo
	else {
		velY -= 500.0f * gameTime * 3;
	}


	bool moved = false;
	if (window->KeyDown(movementKeys.left)) {
		Left();
		moved = true;
	}

	if (window->KeyDown(movementKeys.right)) {
		Right();
		moved = true;
	}

	if (!moved) {
		velX = 0;
	}

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
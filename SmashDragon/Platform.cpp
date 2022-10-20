/**********************************************************************************
// Platform (Código Fonte)
//
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"
#include "GameTest.h"
#include "SmashDragon.h"

// ---------------------------------------------------------------------------------

Platform::Platform(uint type) : width(0), height(0)
{
	this->type = type;
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
	//delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{

}

void Platform::Draw()
{
	float yplayer = SmashDragon::playerOne->Y();
	float scale = 15;

	if (SmashDragon::playerOne->X() > x - width / 2 && SmashDragon::playerOne->X() < x + width / 2 && SmashDragon::playerOne->Y() + SmashDragon::playerOne->height / 2 <= y - height / 2 && y - height / 2 - 20 < SmashDragon::playerOne->Y() + SmashDragon::playerOne->height + 20)
	{
		SmashDragon::shadow->Draw(SmashDragon::playerOne->X(), y - height / 2 - 5, Layer::MIDDLE, 1 / (y - height / 2 - SmashDragon::playerOne->Y() + SmashDragon::playerOne->height / 2) * scale);
	}

	if (SmashDragon::playerTwo->X() > x - width / 2 && SmashDragon::playerTwo->X() < x + width / 2 && SmashDragon::playerTwo->Y() + SmashDragon::playerTwo->height / 2 <= y - height / 2 && y - height / 2 - 20 < SmashDragon::playerTwo->Y() + SmashDragon::playerTwo->height + 20)
	{
		SmashDragon::shadow->Draw(SmashDragon::playerTwo->X(), y - height / 2 - 5, Layer::MIDDLE, 1 / (y - height / 2 - SmashDragon::playerTwo->Y() + SmashDragon::playerTwo->height / 2) * scale);
	}
}

// -------------------------------------------------------------------------------

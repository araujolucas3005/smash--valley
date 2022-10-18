/**********************************************************************************
// Lady (Código Fonte)
//
// Criação:     27 Jan 2013
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto animado
//
**********************************************************************************/

#include "Character.h"
#include "TileSet.h"

// ---------------------------------------------------------------------------------

Character::Character(TileSet* tilesetLeft, TileSet* tilesetRight, Sprite * charImg) : charImg(charImg)
{
	anim = new Animation(tilesetLeft, 0.1f, false);
	animRight = new Animation(tilesetRight, 0.1f, false);
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
	delete anim;
	delete animRight;
}

void Character::AddSec(uint type, uint* sec, uint secSize)
{
	anim->Add(type, sec, secSize);
	animRight->Add(type, sec, secSize);
}
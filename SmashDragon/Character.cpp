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

Character::Character(TileSet* tilesetLeft, TileSet* tilesetRight)
{
	anim = new Animation(tilesetLeft, 0.1f, true);
	animRight = new Animation(tilesetRight, 0.1f, true);
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
	delete anim;
	delete animRight;
}
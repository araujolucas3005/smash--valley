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

Character::Character(string tilesetPath, uint tileWidth, uint tileHeight, uint numCols, uint numTiles)
{
    tileset = new TileSet(tilesetPath, tileWidth, tileHeight, numCols, numTiles);
    anim = new Animation(tileset, 0.060f, true);

   /* uint SeqUp[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };
    uint SeqDown[8] = { 24, 25, 26, 27, 28, 29, 30, 31 };
    uint SeqLeft[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint SeqRight[8] = { 15, 14, 13, 12, 11, 10, 9, 8 };
    uint SeqStill[1] = { 32 };

    // 
    anim->Add(WALKUP, SeqUp, 8);
    anim->Add(WALKDOWN, SeqDown, 8);
    anim->Add(WALKLEFT, SeqLeft, 8);
    anim->Add(WALKRIGHT, SeqRight, 8);
    anim->Add(STILL, SeqStill, 1);*/
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
    delete anim;
    delete tileset;
}
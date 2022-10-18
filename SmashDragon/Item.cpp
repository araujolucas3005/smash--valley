/**********************************************************************************
// Item (Código Fonte)
// 
// Criação:     14 Mai 2012
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define um item de menu
//
**********************************************************************************/

#include "Item.h"

// ---------------------------------------------------------------------------------

Item::Item(float posX, float posY, uint menuId, TileSet* tiles, uint selected[], int sizeSelected, uint unselected[], int sizeUnSelected)
{
    // cria tileset e animação
    tileset = tiles;
    animation = new Animation(tileset, 0.180f, true); 

    // adiciona sequências de animação
    animation->Add(SELECTEDSEQ, selected, sizeSelected);
    animation->Add(NOTSELECTED, unselected, sizeUnSelected);

    // cria bounding box
    BBox(new Rect(-1.0f * tileset->TileWidth() / 2.0f,
                  -1.0f * tileset->TileHeight() / 2.0f,
                  tileset->TileWidth() / 2.0f,
                  tileset->TileHeight() / 2.0f));

    // ajusta posição do item
    MoveTo(posX, posY, Layer::FRONT);
    
    // define o identificador do item
    type = menuId;
}

// ---------------------------------------------------------------------------------

Item::~Item()
{
    delete animation;
    delete tileset;    
}

// -------------------------------------------------------------------------------

void Item::Select()
{
    animation->Select(SELECTEDSEQ);
}

// -------------------------------------------------------------------------------

void Item::UnSelect()
{
    animation->Select(NOTSELECTED);
}

// -------------------------------------------------------------------------------

void Item::Update()
{
    animation->NextFrame();
}

// -------------------------------------------------------------------------------

void Item::Draw()
{
    animation->Draw(x, y, Layer::UPPER);
}

// -------------------------------------------------------------------------------
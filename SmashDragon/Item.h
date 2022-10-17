#ifndef _SMASHDRAGON_ITEM_H_
#define _SMASHDRAGON_ITEM_H_

// ---------------------------------------------------------------------------------

#include "Object.h"
#include "Animation.h"
#include "TileSet.h"
#include "Types.h"

// ---------------------------------------------------------------------------------

enum MenuState { SELECTEDSEQ, NOTSELECTED };

// ---------------------------------------------------------------------------------

class Item : public Object
{
private:
    TileSet* tileset;                // folha de sprites da anima��o
    Animation* animation;              // anima��o do menu

public:
    Item(float posX, float posY, uint menuId, TileSet* tiles, uint selected[], int sizeSelected, uint unselected[], int sizeUnSelected);
    ~Item();

    void Select();                      // seleciona menu
    void UnSelect();                    // desmarca sele��o

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif
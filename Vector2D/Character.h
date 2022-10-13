#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Animation.h"

enum CharacterState { STILL, JUMP, HIT, WALKLEFT, WALKRIGHT };

class Character
{
private:
    TileSet* tileset;              

public:
    Animation* anim;        

    Character(
        string tilesetPath, 
        uint tileWidth = 40,
        uint tileHeight = 60, 
        uint numCols = 8,
        uint numTiles = 40
    );
    ~Character();                         
};

#endif
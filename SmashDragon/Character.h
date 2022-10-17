#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Animation.h"

enum CharacterState { STILL, JUMP, HIT, WALKLEFT, WALKRIGHT, HITTAKEN, DASH, WALKJUMP, MOVINGATTACK, WINNEREND, JUMPUP, JUMPDOWN };

class Character
{
private:
    TileSet* tileset; 
    TileSet* tilesetRight;

public:
    Animation* anim;        
    Animation* animRight;

    Character(TileSet* tilesetLeft, TileSet* tilesetRight);
    ~Character();                         

    void AddSec(uint type, uint* sec, uint secSize);
};

#endif
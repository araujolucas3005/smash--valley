#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Animation.h"

enum CharacterState { STILL, JUMP, HIT, SPAWN, WALKLEFT, WALKRIGHT, HITTAKEN, DASH, WALKJUMP, MOVINGATTACK, WINNEREND, JUMPUP, JUMPDOWN };

class Character
{
private:
    TileSet* tileset; 
    TileSet* tilesetRight;


public:
    Animation* anim;        
    Animation* animRight;
    int index;
    Sprite* charImg;

    Character(TileSet* tilesetLeft, TileSet* tilesetRight, Sprite* charImg);
    ~Character();                         

    void AddSec(uint type, uint* sec, uint secSize);
};

#endif
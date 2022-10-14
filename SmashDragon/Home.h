#ifndef _SMASH_DRAGON_HOME_H_
#define _SMASH_DRAGON_HOME_H_

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

class Home : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo
    TileSet* tileset = nullptr;    // tileset da anima��o
    Animation* anim = nullptr;     // anima��o do menu

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

#endif
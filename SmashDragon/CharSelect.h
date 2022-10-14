#ifndef _SMASH_DRAGON_CHAR_SELECT_H_
#define _SMASH_DRAGON_CHAR_SELECT_H_

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

class CharSelect : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo
    TileSet* tileset = nullptr;    // tileset da anima��o
    Animation* anim = nullptr;     // anima��o do menu

    uint currIndexPlayerOne = 0;
    uint currIndexPlayerTwo = 0;
    int indexPlayerOne = -1;
    int indexPlayerTwo = -1;

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

#endif
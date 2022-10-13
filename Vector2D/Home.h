#ifndef _SMASH_VALLEY_HOME_H_
#define _SMASH_VALLEY_HOME_H_

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

class Home : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo
    TileSet* tileset = nullptr;    // tileset da animação
    Animation* anim = nullptr;     // animação do menu

public:
    void Init();                    // inicia nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza nível
};

#endif
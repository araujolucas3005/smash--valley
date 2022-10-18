#ifndef _SMASH_DRAGON_ENDGAME_H_
#define _SMASH_DRAGON_ENDGAME_H_

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Font.h"

enum { VEGETA, GOKU, GOHAN, VICTORY};


class EndGame : public Game
{
private:
    Sprite* goku = nullptr;
    Sprite* vegeta = nullptr;
    Sprite* gohan = nullptr;
    Sprite* kidGohan = nullptr;
    Audio* audio = nullptr;
    TileSet* tileset = nullptr;
    Animation* animation = nullptr;

    int winner;

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

#endif
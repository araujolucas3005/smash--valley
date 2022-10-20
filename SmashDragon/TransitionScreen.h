#ifndef _SMASH_DRAGON_TRANSITION_H_
#define _SMASH_DRAGON_TRANSITION_H_

#include "Sprite.h"
#include "Resources.h"
#include "Player.h"
#include "Platform.h"
#include "Level.h"

class TransitionScreen : public Game, Level
{
private:
    Timer* transitionTime = nullptr;
    Sprite* stage1_bg = nullptr;
    Sprite* stage2_bg = nullptr;

public:
    void Init();
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();
};

#endif

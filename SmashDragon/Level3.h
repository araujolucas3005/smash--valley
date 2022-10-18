#ifndef _SMASH_DRAGON_LEVEL3_H_
#define _SMASH_DRAGON_LEVEL3_H_

#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "Sprite.h"
#include "Resources.h"
#include "Player.h"
#include "Platform.h"
#include "Level.h"

class Level3 : public Game, Level
{
private:
    Sprite* backg = nullptr;           // pano de fundo
    Audio* audio = nullptr;

    float bgScale = 0.0f;               // escala do pano de fundo

public:
    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
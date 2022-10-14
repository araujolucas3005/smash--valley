#ifndef _SMASH_DRAGON_LEVEL2_H_
#define _SMASH_DRAGON_LEVEL2_H_

#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "Sprite.h"
#include "Resources.h"
#include "Player.h"
#include "Platform.h"

class Level2 : public Game
{
private:
    Sprite* backg = nullptr;           // pano de fundo

    float bgScale = 0.0f;               // escala do pano de fundo

public:
    static Scene* scene;               // gerenciador de cena 

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
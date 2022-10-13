#ifndef _SMASH_VALLEY_LEVEL1_H_
#define _SMASH_VALLEY_LEVEL1_H_

#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "Sprite.h"
#include "Resources.h"
#include "Player.h"
#include "Platform.h"

class Level1 : public Game
{
private:
    Sprite* backg = nullptr;           // pano de fundo

    float bgScale = 0.0f;               // escala do pano de fundo

public:
    static Scene* scene;               // gerenciador de cena 

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif
#ifndef _SMASH_DRAGON_HOME_H_
#define _SMASH_DRAGON_HOME_H_

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Item.h"
#include "Mouse.h"

enum Buttons { PLAY, INSTRUCTIONS };

class Home : public Game
{
private:
    Scene* scene = nullptr;
    Sprite* backg = nullptr;       // pano de fundo
    Sprite* front = nullptr;
    Sprite* instructions = nullptr;
    Image* frontCloudsImage = nullptr;
    Image* backCloudsImage = nullptr;
    float xF;
    float xB;
    Sprite* frontClouds1;
    Sprite* frontClouds2;
    Sprite* backClouds1;
    Sprite* backClouds2;
    TileSet* tilesetPlay = nullptr;    // tileset da anima��o
    TileSet* tilesetInst = nullptr;    // tileset da anima��o
    Item* menu[2] = { 0 };
    Mouse* mouse = nullptr;
    bool passLevel = false;
    bool showInstructions = false;

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

#endif
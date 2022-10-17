#ifndef _SMASH_DRAGON_CHAR_SELECT_H_
#define _SMASH_DRAGON_CHAR_SELECT_H_

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

enum { FORWARD };
enum { VEGETA, SELECT, GOKU, GOHAN, SELECTION, SELECTED, SONG, READYBATTLE};

class CharSelect : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo
    Sprite* infoTop = nullptr;
    Sprite* icones = nullptr;
    TileSet* tileset = nullptr;    // tileset da anima��o
    Animation* animP1 = nullptr;     // anima��o do menu
    Animation* animP2 = nullptr;     // anima��o do menu
    Audio* audio = nullptr;

    int currIndexPlayerOne = 0;
    int currIndexPlayerTwo = 0;
    int indexPlayerOne = -1;
    int indexPlayerTwo = -1;

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

#endif
/**********************************************************************************
// Vector2D (Arquivo de Cabe�alho)
//
// Cria��o:     11 Nov 2011
// Atualiza��o: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Exemplo de utiliza��o da classe Vector
//
**********************************************************************************/

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "Sprite.h"
#include "Resources.h"
#include "Player.h"
#include "Platform.h"

// ------------------------------------------------------------------------------

enum SoundIDs { PULSE, EXPLOSION };

// ------------------------------------------------------------------------------

class Vector2D : public Game
{
private:
    Player* playerOne = nullptr;
    Player* playerTwo = nullptr;
    Platform* platform = nullptr;
    Platform* upPlatform = nullptr;

    Sprite * backg = nullptr;           // pano de fundo
    Sprite * infoBox = nullptr;         // caixa de informa��es
    Sprite * keyMap = nullptr;          // caixa para teclas de atalho    
    
    float bgScale = 0.0f;               // escala do pano de fundo

public:
    static Scene * scene;               // gerenciador de cena 
    static Audio * audio;               // sistema de �udio

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
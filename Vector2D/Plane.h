/**********************************************************************************
// Plane (Arquivo de Cabe�alho)
// 
// Cria��o:     24 Set 2012
// Atualiza��o: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define uma classe para um avi�o
//
**********************************************************************************/

#ifndef _VECTOR2D_PLANE_H_
#define _VECTOR2D_PLANE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                 // objetos do jogo 
#include "Sprite.h"                 // desenho de sprites
#include "Vector.h"                 // representa��o de vetor
#include "Types.h"                  // tipos espec�ficos do motor
#include "Controller.h"             // leitura do controle
#include "Font.h"                   // exibi��o de texto
#include <sstream>                                
using std::stringstream;

// ------------------------------------------------------------------------------

enum ButtonMapping { SHOOT = 0, DPAD = 0, RESTART = 7 };

// ---------------------------------------------------------------------------------

class Plane : public Object
{
private:
    Controller * gamepad;           // entrada via controle
    bool gamepadOn;                 // controle conectado

    Sprite * sprite;                // sprite do avi�o
    Image * missile;                // imagem do m�ssil
    Vector direction;               // dire��o do avi�o

    Font * font;                    // fonte para exibi��o de texto
    stringstream text;              // buffer de texto

public:
    Plane();                        // construtor
    ~Plane();                       // destrutor

    int Width();                    // retorna largura do avi�o
    int Height();                   // retorna altura do avi�o
    float Angle();                  // retorna �ngulo do vetor dire��o

    void Rotate(float angle);       // rota��o (sobrescreve m�todo)
    void Update();                  // atualiza��o
    void Draw();                    // desenho
}; 

// ---------------------------------------------------------------------------------
// fun��es membro inline

inline int Plane::Width()
{ return sprite->Width(); }

inline int Plane::Height()
{ return sprite->Height(); }

inline float Plane::Angle()
{ return direction.angle; }

// ---------------------------------------------------------------------------------

#endif
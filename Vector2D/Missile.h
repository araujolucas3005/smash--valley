/**********************************************************************************
// Missile (Arquivo de Cabe�alho)
// 
// Cria��o:     23 Nov 2011
// Atualiza��o: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define uma classe para um m�ssil/proj�til
//
**********************************************************************************/

#ifndef _VECTOR2D_MISSILE_H_
#define _VECTOR2D_MISSILE_H_

// --------------------------------------------------------------------------------

#include "Object.h"                             // objetos do jogo 
#include "Image.h"                              // carregamento de imagens
#include "Sprite.h"                             // desenho de sprites
#include "Vector.h"                             // representa��o de vetor
#include "Plane.h"                              // objeto avi�o

// --------------------------------------------------------------------------------

class Missile : public Object
{
public:
    Sprite * sprite;                            // sprite do m�ssil
    Vector speed;                               // velocidade do m�ssil

public:
    Missile(Plane * plane, Image * img);        // construtor
    ~Missile();                                 // destrutor

    void Update();                              // atualiza��o
    void Draw();                                // desenho
}; 

// ------------------------------------------------------------------------------

#endif
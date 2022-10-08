/**********************************************************************************
// Vector (Arquivo de Cabe�alho)
// 
// Cria��o:     18 Nov 2011
// Atualiza��o: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Classe para representar um vetor
//
**********************************************************************************/

#ifndef _PROGJOGOS_VECTOR_H_
#define _PROGJOGOS_VECTOR_H_

// --------------------------------------------------------------------------------

#include <cmath>

// --------------------------------------------------------------------------------

class Vector
{
private:
    static const double PI;             // constante PI

public:
    float angle;                        // �ngulo do vetor com o eixo x
    float magnitude;                    // magnitude do vetor

    Vector();                           // construtor padr�o
    Vector(float ang, float mag);       // construtor com �ngulo e magnitude

    void Rotate(float theta);           // rotaciona vetor por �ngulo em graus
    void Scale(float factor);           // amplia ou reduz vetor por um fator

    float X() const;                    // retorna componente X do vetor
    float Y() const;                    // retorna componente Y do vetor
    float Radians() const;              // retorna �ngulo em radianos
}; 

// ---------------------------------------------------------------------------------
// Fun��es Membro Inline

// retorna componente X do vetor
inline float Vector::X() const
{ return magnitude * cos(Radians()); }    

// retorna componente Y do vetor
inline float Vector::Y() const
{ return magnitude * sin(Radians()); }    

// retorna �ngulo em radianos
inline float Vector::Radians() const
{ return float(angle * PI / 180.0); }

// ------------------------------------------------------------------------------



#endif
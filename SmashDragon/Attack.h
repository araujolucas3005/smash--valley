/**********************************************************************************
// Platform (Arquivo de Cabeçalho)
//
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _PLATFORMER_ATTACK_H_
#define _PLATFORMER_ATTACK_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                     // interface de Object

// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------

class Attack : public Object
{
private:
    

public:

    Attack();
    ~Attack();

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Attack::Draw()
{
    //platform->Draw(x, y, z);
}
// ---------------------------------------------------------------------------------

#endif
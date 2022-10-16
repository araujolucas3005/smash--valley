/**********************************************************************************
// Platform (Arquivo de Cabe�alho)
//
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plataformas do jogo
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

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Attack::Draw()
{
    //platform->Draw(x, y, z);
}
// ---------------------------------------------------------------------------------

#endif
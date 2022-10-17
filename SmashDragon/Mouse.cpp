/**********************************************************************************
// Mouse (C�digo Fonte)
//
// Cria��o:     14 Mai 2012
// Atualiza��o: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Gerencia mouse na tela
//
**********************************************************************************/

#include "Mouse.h"

// ---------------------------------------------------------------------------------

Mouse::Mouse()
{
    MoveTo(window->MouseX(), window->MouseY());
    BBox(new Point(x,y));
}

// ---------------------------------------------------------------------------------

Mouse::~Mouse()
{
}

// -------------------------------------------------------------------------------

void Mouse::Update()
{
    MoveTo(window->MouseX(), window->MouseY());
}

// -------------------------------------------------------------------------------

void Mouse::Draw()
{
}

// -------------------------------------------------------------------------------

bool Mouse::Clicked()
{
    if (window->KeyPress(VK_LBUTTON))
        return true;
    else
        return false;
}

// -------------------------------------------------------------------------------
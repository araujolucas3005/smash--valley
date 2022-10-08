/**********************************************************************************
// Plane (C�digo Fonte)
// 
// Cria��o:     24 Set 2012
// Atualiza��o: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define uma classe para um avi�o
//
**********************************************************************************/

#include "Plane.h"
#include "Missile.h"
#include "Vector2D.h"

// ---------------------------------------------------------------------------------

Plane::Plane()
{
    // inicializa controle
    gamepad = new Controller();
    gamepadOn = gamepad->Initialize();

    // cria sprite
    sprite = new Sprite("Resources/Airplane.png");
    missile = new Image("Resources/Missile.png");

    // cria fontes para exibi��o de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    // posi��o, escala e rota��o inicial do avi�o
    MoveTo(window->CenterX(), window->CenterY());
    RotateTo(0);
    ScaleTo(0.5f);

    // dire��o inicial do avi�o
    direction.angle = 90.0f;
    direction.magnitude = 1.0f;
}

// ---------------------------------------------------------------------------------

Plane::~Plane()
{
    delete font;
    delete missile;
    delete sprite;
    delete gamepad;
}
// -------------------------------------------------------------------------------

void Plane::Rotate(float angle)
{
    Object::Rotate(angle);
    direction.Rotate(angle);
}

// -------------------------------------------------------------------------------

void Plane::Update()
{
    // deslocamento padr�o
    float delta = 250 * gameTime;

    // -----------------
    // Teclado
    // -----------------

    // movimenta com as setas
    if (window->KeyDown(VK_RIGHT))
        Translate(delta, 0);
    if (window->KeyDown(VK_LEFT))
        Translate(-delta, 0);
    if (window->KeyDown(VK_UP))
        Translate(0, -delta);
    if (window->KeyDown(VK_DOWN))
        Translate(0, delta);

    // rotaciona avi�o
    if (window->KeyDown('Z'))
        Rotate(-0.5f * delta);
    if (window->KeyDown('X'))
        Rotate(0.5f * delta);

    // reinicia ao estado inicial 
    if (window->KeyDown('R'))
    {
        MoveTo(window->CenterX(), window->CenterY());
        RotateTo(0);
        direction.angle = 90.0f;
        direction.magnitude = 1.0f;
    }

    // dispara m�ssil
    if (window->KeyPress(VK_SPACE))
    {
        Vector2D::audio->Play(PULSE);
        Vector2D::scene->Add(new Missile(this, missile), STATIC);
    }

    // -----------------
    // Controle
    // -----------------

    if (gamepadOn)
    {
        // l� estado atualizado do controle
        gamepad->UpdateState();

        // movimenta com o anal�gico esquerdo
        Translate(gamepad->Axis(AxisX) * 0.25f * gameTime, gamepad->Axis(AxisY) * 0.25f * gameTime);

        // rotaciona com os gatilhos
        Rotate(-delta * gamepad->Axis(AxisZ) * 0.0005f);

        // reinicia posi��o do avi�o
        if (gamepad->ButtonPress(RESTART))
        {
            MoveTo(window->CenterX(), window->CenterY());
            RotateTo(0);
            direction.angle = 90.0f;
            direction.magnitude = 1.0f;
        }

        // movimento com o D-pad
        switch (gamepad->Dpad(DPAD))
        {
        case 0:
            Translate(0.0f, -delta);    // para cima
            break;
        case 4500:
            Translate(delta, -delta);   // para cima e direita
            break;
        case 9000:
            Translate(delta, 0.0f);     // para direita
            break;
        case 13500:
            Translate(delta, delta);    // para baixo e direita
            break;
        case 18000:
            Translate(0.0f, delta);     // para baixo
            break;
        case 22500:
            Translate(-delta, delta);   // para baixo e esquerda
            break;
        case 27000:
            Translate(-delta, 0.0f);   // para esquerda
            break;
        case 31500:
            Translate(-delta, -delta);  // para cima e esquerda
            break;
        }

        // dispara m�ssil
        if (gamepad->ButtonPress(SHOOT))
        {
            Vector2D::audio->Play(PULSE);
            Vector2D::scene->Add(new Missile(this, missile), STATIC);
        }
    }
}

// -------------------------------------------------------------------------------

void Plane::Draw()
{
    // desenha sprite do avi�o
    sprite->Draw(x, y, z, scale, rotation);

    // define cor do texto
    Color textColor{ 0.65f, 0.65f, 0.65f, 1.0f };

    // exibe informa��es sobre o avi�o
    text.str("");
    text << "Deslocamento Vetorial";
    font->Draw(45, 64, text.str(), textColor);

    text.str("");
    text << "Posi��o do avi�o: " << int(x) << " x " << int(y);
    font->Draw(45, 104, text.str(), textColor);

    text.str("");
    text << "Dire��o do Avi�o: " << int(direction.angle) << "�";
    font->Draw(45, 124, text.str(), textColor);

    text.str("");
    text << "M�sseis ativos: " << Vector2D::scene->Size() - 1;
    font->Draw(45, 144, text.str(), textColor);

    if (gamepadOn)
    {
        text.str("");
        text << "A        Disparo       L Stick     Transla��o           Rota��o    LT  RT      Reiniciar     Start";
        font->Draw(window->CenterX() - 218.0f, window->Height() - 6.0f, text.str(), textColor);
    }
    else
    {
        text.str("");
        text << "Espa�o    Disparo        Setas     Transla��o           Rota��o      Z | X       Reiniciar        R";
        font->Draw(window->CenterX() - 233.0f, window->Height() - 6.0f, text.str(), textColor);
    }
}

// -------------------------------------------------------------------------------
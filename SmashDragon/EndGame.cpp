#include "Engine.h"
#include "SmashDragon.h"
#include "EndGame.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void EndGame::Init()
{
    backg = new Sprite("Resources/EndGame/background sprite sheet.png");
    vegeta = new Sprite("Resources/EndGame/vegeta_wins.png");
    goku = new Sprite("Resources/EndGame/goku_wins.png");
    gohan = new Sprite("Resources/EndGame/gohan_wins.png");
    kidGohan = new Sprite("Resources/EndGame/kid_gohan_wins.png");

    if (SmashDragon::playerOnePoints > SmashDragon::playerTwoPoints)
        winner = SmashDragon::playerOne->character->index;
    else
        winner = SmashDragon::playerTwo->character->index;
}

// ------------------------------------------------------------------------------

void EndGame::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        /*   SmashDragon::audio->Stop(MENU);*/
        window->HideCursor(false);
        SmashDragon::audio->Play(MENU);
        SmashDragon::NextLevel<Home>();
    }
    else
    {
        /*anim->NextFrame();*/
    }
}

// ------------------------------------------------------------------------------

void EndGame::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    switch (winner)
    {
    case 0: goku->Draw(window->CenterX(), window->CenterY(), Layer::FRONT); break;
    case 1: gohan->Draw(window->CenterX(), window->CenterY(), Layer::FRONT); break;
    case 2: vegeta->Draw(window->CenterX(), window->CenterY(), Layer::FRONT); break;
    case 3: kidGohan->Draw(window->CenterX(), window->CenterY(), Layer::FRONT); break;
    }
}

// ------------------------------------------------------------------------------

void EndGame::Finalize()
{
    SmashDragon::playerOne->Reset();
    SmashDragon::playerTwo->Reset();

    SmashDragon::playerOnePoints = 3;
    SmashDragon::playerTwoPoints = 3;

    delete backg;
    delete goku;
    delete vegeta;
    delete gohan;
    delete kidGohan;
}

// ------------------------------------------------------------------------------
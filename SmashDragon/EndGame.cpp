#include "Engine.h"
#include "SmashDragon.h"
#include "EndGame.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void EndGame::Init()
{
    tileset = new TileSet("Resources/EndGame/background sprite sheet.png", 1200, 640, 4, 4);
    animation = new Animation(tileset, 0.1f, true);
    vegeta = new Sprite("Resources/EndGame/vegeta_wins.png");
    goku = new Sprite("Resources/EndGame/goku_wins.png");
    gohan = new Sprite("Resources/EndGame/gohan_wins.png");
    kidGohan = new Sprite("Resources/EndGame/kid_gohan_wins.png");
    

    audio = new Audio();
    audio->Add(GOKU, "Resources/EndGame/goku_win.wav");
    audio->Add(VEGETA, "Resources/EndGame/vegeta_win.wav");
    audio->Add(GOHAN, "Resources/EndGame/gohan_win.wav");
    audio->Add(VICTORY,"Resources/EndGame/VictoryTheme.wav");
    audio->Play(VICTORY);

    if (SmashDragon::playerOnePoints > SmashDragon::playerTwoPoints)
        winner = SmashDragon::playerOne->character->index;
    else
        winner = SmashDragon::playerTwo->character->index;

    switch (winner)
    {
    case 0: audio->Play(GOKU); break;
    case 1: case 3: audio->Play(GOHAN); break;
    case 2: audio->Play(VEGETA); break;
    }
}

// ------------------------------------------------------------------------------

void EndGame::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla SPACE for pressionada
    if (window->KeyPress(VK_SPACE))
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
    
    animation->NextFrame();
}

// ------------------------------------------------------------------------------

void EndGame::Draw()
{
    animation->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

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

    delete goku;
    delete vegeta;
    delete gohan;
    delete kidGohan;
    delete audio;
}

// ------------------------------------------------------------------------------
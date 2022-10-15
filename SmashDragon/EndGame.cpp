#include "Engine.h"
#include "SmashDragon.h"
#include "EndGame.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void EndGame::Init()
{
    //backg = new Sprite("Resources/TitleScreen.png");
    //tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    //anim = new Animation(tileset, 0.180f, true);
    //GravityGuy::audio->Play(MENU, true);
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
    /* backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
     anim->Draw(545, 275);*/

    string result;
    if (SmashDragon::playerOnePoints > SmashDragon::playerTwoPoints)
        result = "Jogador 1";
    else
        result = "Jogador 2";

    Color blue{ 0.60f, 0.60f, 0.65f, 1.0f };
    SmashDragon::bold->Draw(window->CenterX() - 50, window->CenterY(), "Vencedor: " + result, blue);
}

// ------------------------------------------------------------------------------

void EndGame::Finalize()
{
    SmashDragon::playerOne->Reset();
    SmashDragon::playerTwo->Reset();

    SmashDragon::playerOnePoints = 3;
    SmashDragon::playerTwoPoints = 3;

    /*delete anim;
    delete tileset;
    delete backg;*/
}

// ------------------------------------------------------------------------------
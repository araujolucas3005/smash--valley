#include "SmashDragon.h"
#include "TransitionScreen.h"
#include "Engine.h"
#include "Level2.h"
#include "Level3.h"

// ------------------------------------------------------------------------------

void TransitionScreen::Init()
{
    transitionTime = new Timer();
    transitionTime->Start();
}

// ------------------------------------------------------------------------------

void TransitionScreen::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (transitionTime->Elapsed() > 1.5f)
    {
        if (SmashDragon::round == 2)
            SmashDragon::NextLevel<Level2>();
        else
            SmashDragon::NextLevel<Level3>();
    }

}

// ------------------------------------------------------------------------------

void TransitionScreen::Draw()
{
    string text = "Round " + to_string(SmashDragon::round) + " de 3";
    SmashDragon::bold->Draw(window->CenterX() - 75, 115, text, {1, 1, 1, 1}, Layer::FRONT, 2.0f);

    SmashDragon::playerOne->character->charImg->Draw(window->CenterX() - 30, 270, Layer::FRONT, 0.15f);
    SmashDragon::playerTwo->character->charImg->Draw(window->CenterX() - 30, 360, Layer::FRONT, 0.15f);

    string points = to_string(3 - SmashDragon::playerTwoPoints);
    SmashDragon::bold->Draw(window->CenterX() + 35, 280, points, { 1, 1, 1, 1 }, Layer::FRONT, 1.2f);
    points = to_string(3 - SmashDragon::playerOnePoints);
    SmashDragon::bold->Draw(window->CenterX() + 35, 370, points, { 1, 1, 1, 1 }, Layer::FRONT, 1.2f);
}

// ------------------------------------------------------------------------------

void TransitionScreen::Finalize()
{
    delete transitionTime;
}
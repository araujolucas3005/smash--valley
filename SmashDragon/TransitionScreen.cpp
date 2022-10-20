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
    stage1_bg = new Sprite("Resources/stage1_bg.png");
    stage2_bg = new Sprite("Resources/stage2_bg.png");
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
    if (SmashDragon::round <= 2)
        stage1_bg->Draw(window->CenterX(), window->CenterY());
    else
        stage2_bg->Draw(window->CenterX(), window->CenterY());

    string text = "Round " + to_string(SmashDragon::round) + " of 3";
    SmashDragon::bold->Draw(window->CenterX() - 65, 115, text, {1, 1, 1, 1}, Layer::FRONT, 3.0f);

    SmashDragon::playerOne->character->charImgTransition->Draw(window->CenterX() - 30, 263, Layer::FRONT, 0.4f);
    SmashDragon::playerTwo->character->charImgTransition->Draw(window->CenterX() - 30, 353, Layer::FRONT, 0.4f);

    string points = to_string(3 - SmashDragon::playerTwoPoints);
    SmashDragon::bold->Draw(window->CenterX() + 45, 280, points, { 1, 1, 1, 1 }, Layer::FRONT, 2.2f);
    points = to_string(3 - SmashDragon::playerOnePoints);
    SmashDragon::bold->Draw(window->CenterX() + 45, 380, points, { 1, 1, 1, 1 }, Layer::FRONT, 2.2f);
}

// ------------------------------------------------------------------------------

void TransitionScreen::Finalize()
{
    delete transitionTime;
}
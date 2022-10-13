#include "Engine.h"
#include "SmashValley.h"
#include "CharSelect.h"

// ------------------------------------------------------------------------------
// DEIXAR OS DOIS PLAYERS ESCOLHEREM AO MESMO TEMPO

void CharSelect::Init()
{
    //backg = new Sprite("Resources/TitleScreen.png");
    //tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    //anim = new Animation(tileset, 0.180f, true);
    //GravityGuy::audio->Play(MENU, true);
}

// ------------------------------------------------------------------------------

void CharSelect::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    bool allSelected = true;

    if (indexPlayerOne != -1) 
    {
        allSelected = false;

        if (window->KeyPress(SmashValley::playerOne->mk.left) && indexPlayerTwo != currIndexPlayerOne - 1 && currIndexPlayerOne - 1 >= 0)
        {
            currIndexPlayerOne--;
        }
        else if (window->KeyPress(SmashValley::playerOne->mk.right) && indexPlayerTwo != currIndexPlayerOne + 1 && currIndexPlayerOne + 1 < 4)
        {
            currIndexPlayerOne++;
        }
        else if (window->KeyPress(SmashValley::playerOne->mk.attack))
        {
            indexPlayerOne = currIndexPlayerOne;

            SmashValley::playerOne->character = SmashValley::characters[indexPlayerOne];
        }
    }

    if (indexPlayerTwo != -1)
    {
        allSelected = false;

        if (window->KeyPress(SmashValley::playerTwo->mk.left) && indexPlayerOne != currIndexPlayerTwo - 1 && currIndexPlayerTwo - 1 >= 0)
        {
            currIndexPlayerTwo--;
        }
        else if (window->KeyPress(SmashValley::playerTwo->mk.right) && indexPlayerOne != currIndexPlayerTwo + 1 && currIndexPlayerTwo + 1 < 4)
        {
            currIndexPlayerTwo++;
        }
        else if (window->KeyPress(SmashValley::playerTwo->mk.attack))
        {
            indexPlayerOne = currIndexPlayerOne;

            SmashValley::playerTwo->character = SmashValley::characters[indexPlayerTwo];
        }
    }

    if (allSelected = false) {
        // MANDA PRO LEVEL1
    }
}

// ------------------------------------------------------------------------------

void CharSelect::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(545, 275);
}

// ------------------------------------------------------------------------------

void CharSelect::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
}

// ------------------------------------------------------------------------------
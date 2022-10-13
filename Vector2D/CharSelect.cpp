#include "Engine.h"
#include "Level1.h"
#include "SmashValley.h"
#include "CharSelect.h"

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
    OutputDebugString("test");

    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    bool allSelected = true;

    if (indexPlayerOne == -1) 
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

            if (currIndexPlayerTwo == indexPlayerOne && indexPlayerTwo != -1)
            {
                if (currIndexPlayerTwo + 1 < 4)
                {
                    currIndexPlayerTwo++;
                }
                else if (currIndexPlayerTwo - 1 > 0)
                {
                    currIndexPlayerTwo--;
                }
            }

            // DESCOMENTAR QUANDO DER NEW NO CHARACTER LÁ NO SmashValley.cpp
            /*SmashValley::playerOne->character = SmashValley::characters[indexPlayerOne];*/
        }
    }

    if (indexPlayerTwo == -1)
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
        else if (window->KeyPress(/*SmashValley::playerTwo->mk.attack*/'P'))
        {
            indexPlayerTwo = currIndexPlayerTwo;

            if (currIndexPlayerOne == indexPlayerTwo && indexPlayerOne != -1)
            {
                if (currIndexPlayerOne + 1 < 4)
                {
                    currIndexPlayerOne++;
                }
                else if (currIndexPlayerOne - 1 > 0)
                {
                    currIndexPlayerOne--;
                }
            }

           // DESCOMENTAR QUANDO DER NEW NO CHARACTER LÁ NO SmashValley.cpp
           /* SmashValley::playerTwo->character = SmashValley::characters[indexPlayerTwo];*/
        }
    }

    OutputDebugString(allSelected ? "selecionados\n" : "não\n");

    if (allSelected) {
        SmashValley::NextLevel<Level1>();
    }
}

// ------------------------------------------------------------------------------

void CharSelect::Draw()
{
   /* backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(545, 275);*/
}

// ------------------------------------------------------------------------------

void CharSelect::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
}

// ------------------------------------------------------------------------------
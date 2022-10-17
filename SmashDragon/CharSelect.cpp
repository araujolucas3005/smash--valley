#include "Engine.h"
#include "Level1.h"
#include "SmashDragon.h"
#include "CharSelect.h"

void CharSelect::Init()
{
    backg = new Sprite("Resources/CharSelection/fundo.png");
    infoTop = new Sprite("Resources/CharSelection/top.png");
    icones = new Sprite("Resources/CharSelection/icones.png");
    tileset = new TileSet("Resources/CharSelection/selection_square_Sprite_Sheet.png", 205, 205, 5, 5);
    uint seq[] = { 0, 1, 2, 3, 4, 4, 3, 2, 1, 0 };

    animP1 = new Animation(tileset, 0.090f, true);
    animP1->Add(FORWARD, seq, 10);
    animP1->Select(FORWARD);

    animP2 = new Animation(tileset, 0.180f, false);
    animP2->Add(FORWARD, seq, 10);
    animP2->Select(FORWARD);
    
    audio = new Audio();
    audio->Add(GOKU, "Resources/CharSelection/goku.wav");
    audio->Add(VEGETA, "Resources/CharSelection/vegeta.wav");
    audio->Add(GOHAN, "Resources/CharSelection/gohan.wav");
    audio->Add(SELECT, "Resources/CharSelection/select_your_fighter.wav");
    audio->Add(SONG, "Resources/CharSelection/selection_song.wav");
    audio->Add(SELECTION, "Resources/CharSelection/SelectionSound.wav", 2);
    audio->Add(SELECTED, "Resources/CharSelection/SelectedSound.wav", 2);

    audio->Volume(SELECTION, 0.6);
    audio->Volume(SELECTED, 0.6);

    audio->Volume(SONG, 0.4);
    audio->Play(SONG, true);
    audio->Play(SELECT);
}

// ------------------------------------------------------------------------------

void CharSelect::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    //if (window->KeyPress(VK_RETURN))
    //{
    //    /*   SmashDragon::audio->Stop(MENU);*/
    //    SmashDragon::NextLevel<Level1>();
    //}

    bool allSelected = true;

    if (indexPlayerOne == -1) 
    {
        allSelected = false;

        if (window->KeyPress(SmashDragon::playerOne->mk.left))
        {
            if (indexPlayerTwo == currIndexPlayerOne - 1)
            {
                if (currIndexPlayerOne - 2 >= 0)
                {
                    currIndexPlayerOne -= 2;
                }
            }
            else if (currIndexPlayerOne - 1 >= 0)
            {
                currIndexPlayerOne--;
            }
        }
        else if (window->KeyPress(SmashDragon::playerOne->mk.right))
        {
            if (indexPlayerTwo == currIndexPlayerOne + 1)
            {
                if (currIndexPlayerOne + 2 < 4)
                {
                    currIndexPlayerOne += 2;
                }
            }
            else if (currIndexPlayerOne + 1 < 4)
            {
                currIndexPlayerOne++;
            }

            audio->Play(SELECTION);
        }
        else if (window->KeyPress(SmashDragon::playerOne->mk.attack))
        {
            indexPlayerOne = currIndexPlayerOne;

            if (currIndexPlayerTwo == indexPlayerOne)
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

            // DESCOMENTAR QUANDO DER NEW NO CHARACTER L� NSmashDragoney.cpp
            SmashDragon::playerOne->character = SmashDragon::characters[indexPlayerOne];
            audio->Play(SELECTED);

            switch (indexPlayerOne)
            {
                case 0: audio->Play(GOKU); break;
                case 1: case 3: audio->Play(GOHAN); break;
                case 2: audio->Play(VEGETA); break;
            }
        }
    }

    if (indexPlayerTwo == -1)
    {
        allSelected = false;

        if (window->KeyPress(SmashDragon::playerTwo->mk.left))
        {
            if (indexPlayerOne == currIndexPlayerTwo - 1)
            {
                if (currIndexPlayerTwo - 2 >= 0)
                {
                    currIndexPlayerTwo -= 2;
                }
            }
            else if (currIndexPlayerTwo - 1 >= 0)
            {
                currIndexPlayerTwo--;
            }

            audio->Play(SELECTION);
        }
        else if (window->KeyPress(SmashDragon::playerTwo->mk.right))
        {
            if (indexPlayerOne == currIndexPlayerTwo + 1)
            {
                if (currIndexPlayerTwo + 2 < 4)
                {
                    currIndexPlayerTwo += 2;
                }
            }
            else if (currIndexPlayerTwo + 1 < 4)
            {
                currIndexPlayerTwo++;
            }

            audio->Play(SELECTION);
        }
        else if (window->KeyPress(/*SmashDragon::playerTwo->mk.attack*/'P'))
        {
            indexPlayerTwo = currIndexPlayerTwo;

            if (currIndexPlayerOne == indexPlayerTwo)
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

           // DESCOMENTAR QUANDO DER NEW NO CHARACTER L� NSmashDragoney.cpp
            SmashDragon::playerTwo->character = SmashDragon::characters[indexPlayerTwo];
            audio->Play(SELECTED);

            switch (indexPlayerTwo)
            {
            case 0: audio->Play(GOKU); break;
            case 1: case 3: audio->Play(GOHAN); break;
            case 2: audio->Play(VEGETA); break;
            }
        }
    }

    if (allSelected) {
        SmashDragon::NextLevel<Level1>();
    }
    else
    {
        animP1->NextFrame();
        animP2->NextFrame();
    }
}

// ------------------------------------------------------------------------------

void CharSelect::Draw()
{
   backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
   infoTop->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
   icones->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
   SmashDragon::charactersSelectImg[currIndexPlayerOne]->Draw(window->CenterX() - 350, window->CenterY(), Layer::MIDDLE);
   SmashDragon::charactersSelectImg[currIndexPlayerTwo]->Draw(window->CenterX() + 350, window->CenterY(), Layer::MIDDLE);
   animP1->Draw(370 + (167 * currIndexPlayerOne), window->Height() - 130, Layer::FRONT, 1, 0, { 1, 1, 1, 1});
   animP2->Draw((window->Width() - 330) - (167 * (3 - currIndexPlayerTwo)), window->Height() - 130, Layer::FRONT, 1, 0, { 1, 1, 1, 1 });
}

// ------------------------------------------------------------------------------

void CharSelect::Finalize()
{
    delete animP1;
    delete animP2;
    delete tileset;
    delete backg;
    delete infoTop;
    delete icones;
    delete audio;
}

// ------------------------------------------------------------------------------
#include "Engine.h"
#include "SmashDragon.h"
#include "Home.h"
#include "CharSelect.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    scene = new Scene();

    backg = new Sprite("Resources/Home/fundo.png");
    instructions = new Sprite("Resources/Home/tela_controles.png");
    front = new Sprite("Resources/Home/frente.png");
    xF = xB = window->CenterX();

    frontCloudsImage = new Image("Resources/Home/nuvens_meio_frente.png");
    frontClouds1 = new Sprite(frontCloudsImage);
    frontClouds2 = new Sprite(frontCloudsImage);

    backCloudsImage = new Image("Resources/Home/nuvens_grandes_meio_atras.png");
    backClouds1 = new Sprite(backCloudsImage);
    backClouds2 = new Sprite(backCloudsImage);


    tilesetPlay = new TileSet("Resources/Home/play_button_rz.png", 190, 111, 2, 2);
    uint seq1[] = {0, 1};
    uint seq2[] = {0};
    menu[0] = new Item(window->CenterX(), window->Height() - 95, PLAY, tilesetPlay, seq1, 2, seq2, 1);

    tilesetInst = new TileSet("Resources/Home/controls_sprite.png", 115, 115, 15, 15);
    uint seq3[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    uint seq4[] = { 0 };
    menu[1] = new Item(window->CenterX() + 500, window->Height() - 95, INSTRUCTIONS, tilesetInst, seq3, 15, seq4, 1);

    for (int i = 0; i < 2; i++)
        scene->Add(menu[i], STATIC);

    mouse = new Mouse();
    scene->Add(mouse, MOVING);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // atualiza objeto mouse
    mouse->Update();

    xF -= (80 * gameTime);
    xB += (60 * gameTime);

    for (int i = 0; i < 2; i++)
    {
        if (scene->Collision(mouse, menu[i]))
        {
            menu[i]->Select();

            switch (menu[i]->Type())
            {
                case PLAY: if (mouse->Clicked()) passLevel = true; break;
                case INSTRUCTIONS: showInstructions = true; break;
            }
        }
        else
        {
            menu[i]->UnSelect();
            showInstructions = false;
        }

        menu[i]->Update();
    }

    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN) || passLevel)
    {
        passLevel = false;
        SmashDragon::audio->Stop(MENU);
        window->HideCursor(true);
        SmashDragon::NextLevel<CharSelect>();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    if (showInstructions)
        instructions->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);

    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    front->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);

    // desenha prédios mais distantes
    backClouds1->Draw(xB, window->CenterY() + 10, Layer::MIDDLE);
    backClouds2->Draw(xB - backCloudsImage->Width(), window->CenterY() + 10, Layer::MIDDLE);

    if (xB > backCloudsImage->Width())
        xB = 0;

    // desenha prédios mais próximos
    frontClouds1->Draw(xF, window->Height() - 150, Layer::UPPER);
    frontClouds2->Draw(xF + frontCloudsImage->Width(), window->Height() - 150, Layer::UPPER);

    // traz pano de fundo de volta para dentro da tela
    if (xF + frontCloudsImage->Width() / 2.0f < 0)
        xF += frontCloudsImage->Width();

    

    scene->Draw();
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
    delete front;
    delete frontClouds1;
    delete frontClouds2;
    delete frontCloudsImage;
    delete backClouds1;
    delete backClouds2;
    delete backCloudsImage;
    delete scene;
    delete instructions;
}

// ------------------------------------------------------------------------------
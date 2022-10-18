
#include "Engine.h"
#include "Level1.h"
#include "Level2.h"
#include "SmashDragon.h"
#include "GameTest.h"

// ------------------------------------------------------------------------------

void Level1::Init()
{
	// carrega pain�is e pano de fundo
	backg = new Sprite("Resources/Stage1.png");

	// PEGAR AS PLATAFORMAS DE UM ARQUIVO
	Platform* platform = new Platform(PLATFORM);
	platform->width = 800;
	platform->height = 140;
	platform->BBox(new Rect(-400, -70, 400, 70));
	platform->MoveTo(window->CenterX(), 500);

	Platform* upPlatform1 = new Platform(TRAVERSABLE_PLATFORM);
	upPlatform1->width = 250;
	upPlatform1->height = 20;
	upPlatform1->BBox(new Rect(-125, -10, 125, 10));
	upPlatform1->MoveTo(250, 300);

	Platform* upPlatform2 = new Platform(TRAVERSABLE_PLATFORM);
	upPlatform2->width = 250;
	upPlatform2->height = 20;
	upPlatform2->BBox(new Rect(-125, -10, 125, 10));
	upPlatform2->MoveTo(window->Width() - 250, 300);

	scene = new Scene();
	scene->Add(SmashDragon::playerOne, MOVING);
	scene->Add(SmashDragon::playerTwo, MOVING);
	scene->Add(platform, STATIC);
	scene->Add(upPlatform1, STATIC);
	scene->Add(upPlatform2, STATIC);

	SmashDragon::playerOne->MoveTo(window->CenterX() - 100, window->CenterY() - 100);
	SmashDragon::playerTwo->MoveTo(window->CenterX() + 100, window->CenterY() - 100);

	levelEndingTimer = new Timer();
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	// sai com o pressionar do ESC
	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	// atualiza��o da cena
	scene->Update();
	scene->CollisionDetection();

	if (SmashDragon::passLevel)
	{
		if (ended)
		{
			if (levelEndingTimer->Elapsed(5.0f))
			{
				SmashDragon::passLevel = false;
				SmashDragon::NextLevel<Level2>();
			}
		}
		else
		{
			SmashDragon::playerOne->character->anim->Restart();
			SmashDragon::playerTwo->character->anim->Restart();

			levelEndingTimer->Reset();
			ended = true;
		}
	}
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	// desenha pano de fundo
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	scene->Draw();

	if (SmashDragon::viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	scene->Remove(SmashDragon::playerOne, MOVING);
	scene->Remove(SmashDragon::playerTwo, MOVING);

	SmashDragon::playerOne->ResetAfterLevel();
	SmashDragon::playerTwo->ResetAfterLevel();

	delete scene;
	delete backg;
}


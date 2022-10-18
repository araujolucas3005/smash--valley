
#include "Engine.h"
#include "Level2.h"
#include "Level3.h"
#include "SmashDragon.h"
#include "GameTest.h"

// ------------------------------------------------------------------------------

void Level2::Init()
{
	// carrega pain�is e pano de fundo
	//backg = new Sprite("Resources/Kamikaze.jpg");

	// PEGAR AS PLATAFORMAS DE UM ARQUIVO
	Platform* platform1 = new Platform(TRAVERSABLE_PLATFORM);
	platform1->width = 250;
	platform1->height = 20;
	platform1->BBox(new Rect(-125, -10, 125, 10));
	platform1->MoveTo(window->CenterX(), 250);

	Platform* platform2 = new Platform(TRAVERSABLE_PLATFORM);
	platform2->width = 300;
	platform2->height = 20;
	platform2->BBox(new Rect(-150, -10, 150, 10));
	platform2->MoveTo(250, 500);

	Platform* platform3 = new Platform(TRAVERSABLE_PLATFORM);
	platform3->width = 300;
	platform3->height = 20;
	platform3->BBox(new Rect(-150, -10, 150, 10));
	platform3->MoveTo(window->Width() - 250, 500);

	scene = new Scene();
	scene->Add(SmashDragon::playerOne, MOVING);
	scene->Add(SmashDragon::playerTwo, MOVING);
	scene->Add(platform1, STATIC);
	scene->Add(platform2, STATIC);
	scene->Add(platform3, STATIC);

	SmashDragon::playerOne->MoveTo(250, window->CenterY() - 100);
	SmashDragon::playerTwo->MoveTo(window->Width() - 250, window->CenterY() - 100);

	levelEndingTimer = new Timer();
}

// ------------------------------------------------------------------------------

void Level2::Update()
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
			if (levelEndingTimer->Elapsed(3.0f))
			{
				SmashDragon::passLevel = false;
				SmashDragon::NextLevel<Level3>();
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

void Level2::Draw()
{
	// desenha pano de fundo
	//backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, bgScale);

	SmashDragon::playerOne->character->charImg->Draw(50, 50, Layer::FRONT, 0.15f);
	SmashDragon::playerTwo->character->charImg->Draw(window->Width() - 50, 50, Layer::FRONT, 0.15f);
	SmashDragon::bold->Draw(30, 30, (std::to_string(SmashDragon::playerOne->life)).c_str(), { 0, 0, 0, 1 }, Layer::FRONT, 1.2f);
	SmashDragon::bold->Draw(window->Width() + 2, 30, (std::to_string(SmashDragon::playerTwo->life)).c_str(), { 0, 0, 0, 1 }, Layer::FRONT, 1.2f);

	SmashDragon::bold->Draw(110, 70, (std::to_string(int((SmashDragon::playerOne->hits - 2) * 12)) + "%").c_str(), { 0, 0, 0, 1 }, Layer::FRONT, 1.2f);
	SmashDragon::bold->Draw(window->Width() - 90, 70, (std::to_string(int((SmashDragon::playerTwo->hits - 2) * 12)) + "%").c_str(), { 0, 0, 0, 1 }, Layer::FRONT, 1.2f);

	scene->Draw();

	if (SmashDragon::viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
	scene->Remove(SmashDragon::playerOne, MOVING);
	scene->Remove(SmashDragon::playerTwo, MOVING);

	SmashDragon::playerOne->ResetAfterLevel();
	SmashDragon::playerTwo->ResetAfterLevel();

	delete scene;
	delete backg;
}



#include "Engine.h"
#include "Level3.h"

#include "EndGame.h"
#include "SmashDragon.h"
#include "GameTest.h"

// ------------------------------------------------------------------------------

void Level3::Init()
{
	// carrega pain�is e pano de fundo
	//backg = new Sprite("Resources/Kamikaze.jpg");

	// PEGAR AS PLATAFORMAS DE UM ARQUIVO
	Platform* platform = new Platform(PLATFORM);
	platform->width = 800;
	platform->height = 140;
	platform->BBox(new Rect(-400, -70, 400, 70));
	platform->MoveTo(window->CenterX(), 550);

	scene = new Scene();
	scene->Add(SmashDragon::playerOne, MOVING);
	scene->Add(SmashDragon::playerTwo, MOVING);
	scene->Add(platform, STATIC);

	SmashDragon::playerOne->MoveTo(window->CenterX() - 250, window->CenterY() - 100);
	SmashDragon::playerTwo->MoveTo(window->CenterX() + 250, window->CenterY() - 100);

	levelEndingTimer = new Timer();
}

// ------------------------------------------------------------------------------

void Level3::Update()
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
				SmashDragon::NextLevel<EndGame>();
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

void Level3::Draw()
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

void Level3::Finalize()
{
	scene->Remove(SmashDragon::playerOne, MOVING);
	scene->Remove(SmashDragon::playerTwo, MOVING);

	SmashDragon::playerOne->ResetAfterLevel();
	SmashDragon::playerTwo->ResetAfterLevel();

	delete scene;
	delete backg;
}


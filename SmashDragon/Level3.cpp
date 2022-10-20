
#include "Engine.h"
#include "Level3.h"

#include "EndGame.h"
#include "SmashDragon.h"
#include "GameTest.h"

// ------------------------------------------------------------------------------

void Level3::Init()
{
	// carrega pain�is e pano de fundo
	backg = new Sprite("Resources/Stage3.png");
	SmashDragon::audio->Play(FIGHT);
	SmashDragon::audio->Play(L3THEME, true);

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
				SmashDragon::round = 1;
			
				SmashDragon::NextLevel<EndGame>();
			}
		}
		else
		{
			SmashDragon::audio->Stop(L3THEME);
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
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, { 1, 1, 1, 0.8 });

	SmashDragon::playerOne->character->hpImg->Draw(145, 55, Layer::FRONT, 0.7f);
	SmashDragon::playerTwo->character->hpImg->Draw(window->Width() - 145, 55, Layer::FRONT, 0.7f);

	float gap = 0;
	for (int i = 0; i < SmashDragon::playerOne->life; i++)
	{
		SmashDragon::dragonballs[i]->Draw(145.0f + gap, 70.0f, Layer::FRONT);
		gap += 40;
	}

	gap = 0;
	for (int i = 0; i < SmashDragon::playerTwo->life; i++)
	{
		SmashDragon::dragonballs[i]->Draw(window->Width() - 65.0f - gap, 70.0f, Layer::FRONT);
		gap += 40;
	}

	SmashDragon::bold->Draw(215.f, 45.0f, (std::to_string(int((SmashDragon::playerOne->hits - 2) * 12)) + "%").c_str(), { 1, 1, 1, 1 }, Layer::FRONT, 1.2f);
	SmashDragon::bold->Draw(window->Width() - 75.0f, 45.0f, (std::to_string(int((SmashDragon::playerTwo->hits - 2) * 12)) + "%").c_str(), { 1, 1, 1, 1 }, Layer::FRONT, 1.2f);

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


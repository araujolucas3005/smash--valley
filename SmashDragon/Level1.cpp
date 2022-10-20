
#include "Engine.h"
#include "Level1.h"
#include "Level2.h"
#include "TransitionScreen.h"
#include "SmashDragon.h"
#include "GameTest.h"

// ------------------------------------------------------------------------------

void Level1::Init()
{
	// carrega pain�is e pano de fundo
	backg = new Sprite("Resources/Stage1.png");
	SmashDragon::audio->Play(FIGHT);
	SmashDragon::audio->Play(L1THEME);

	// PEGAR AS PLATAFORMAS DE UM ARQUIVO
	Platform* platform = new Platform(PLATFORM);
	platform->width = 800;
	platform->height = 160;
	platform->BBox(new Rect(-400, -80, 400, 80));
	platform->MoveTo(window->CenterX(), 515);

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

	SmashDragon::playerOne->life = 4;
	SmashDragon::playerTwo->life = 4;

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
			if (levelEndingTimer->Elapsed(3.0f))
			{
				SmashDragon::passLevel = false;
				SmashDragon::round = 2;
			
				SmashDragon::NextLevel<TransitionScreen>();
			}
		}
		else
		{
			SmashDragon::audio->Stop(L1THEME);
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
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, {1, 1, 1, 0.8});

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

	SmashDragon::bold->Draw(215.f, 52.0f, (std::to_string(int((SmashDragon::playerOne->hits - 2) * 12)) + "%").c_str(), {1, 1, 1, 1}, Layer::FRONT, 2.0f);
	SmashDragon::bold->Draw(window->Width() - 75.0f, 52.0f, (std::to_string(int((SmashDragon::playerTwo->hits - 2) * 12)) + "%").c_str(), { 1, 1, 1, 1 }, Layer::FRONT, 2.0f);

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


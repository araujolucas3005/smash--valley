
#include "Engine.h"
#include "Level2.h"
#include "Level3.h"
#include "TransitionScreen.h"
#include "SmashDragon.h"
#include "GameTest.h"
#include "EndGame.h"

// ------------------------------------------------------------------------------

void Level2::Init()
{
	// carrega pain�is e pano de fundo
	backg = new Sprite("Resources/Stage2.png");
	SmashDragon::audio->Play(FIGHT);
	SmashDragon::audio->Play(L2THEME, true);

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
				SmashDragon::round = 3;

				if (SmashDragon::playerOnePoints > SmashDragon::playerTwoPoints || SmashDragon::playerOnePoints < SmashDragon::playerTwoPoints)
					SmashDragon::NextLevel<EndGame>();
				else
					SmashDragon::NextLevel<TransitionScreen>();
			}
		}
		else
		{
			SmashDragon::audio->Stop(L2THEME);
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
	// desenha plano de fundo
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

void Level2::Finalize()
{
	scene->Remove(SmashDragon::playerOne, MOVING);
	scene->Remove(SmashDragon::playerTwo, MOVING);

	SmashDragon::playerOne->ResetAfterLevel();
	SmashDragon::playerTwo->ResetAfterLevel();

	delete scene;
	delete backg;
}


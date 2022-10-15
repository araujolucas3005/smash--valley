
#include "Engine.h"
#include "Level3.h"
#include "EndGame.h"
#include "SmashDragon.h"
#include "GameTest.h"

Scene* Level3::scene = nullptr;

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

	if (SmashDragon::passLevel == true)
	{
		SmashDragon::passLevel = false;
		SmashDragon::NextLevel<EndGame>();
	}
}

// ------------------------------------------------------------------------------

void Level3::Draw()
{
	// desenha pano de fundo
	//backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, bgScale);

	scene->Draw();

	/*if (SmashDragon::viewBBox)*/
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


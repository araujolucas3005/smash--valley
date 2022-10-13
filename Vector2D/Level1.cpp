
#include "Engine.h"
#include "Level1.h"
#include "SmashValley.h"
#include "GameTest.h"

Scene* Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
	// carrega painéis e pano de fundo
	//backg = new Sprite("Resources/Kamikaze.jpg");

	// PEGAR AS PLATAFORMAS DE UM ARQUIVO
	Platform * platform = new Platform(PLATFORM);
	platform->width = 800;
	platform->height = 140;
	platform->BBox(new Rect(-400, -70, 400, 70));
	platform->MoveTo(window->CenterX(), 500);

	Platform* upPlatform = new Platform(TRAVERSABLE_PLATFORM);
	upPlatform->width = 800;
	upPlatform->height = 20;
	upPlatform->BBox(new Rect(-400, -10, 400, 10));
	upPlatform->MoveTo(window->CenterX(), 300);

	scene = new Scene();
	scene->Add(SmashValley::playerOne, MOVING);
	scene->Add(SmashValley::playerTwo, MOVING);
	scene->Add(platform, STATIC);
	scene->Add(upPlatform, STATIC);

	SmashValley::playerOne->MoveTo(window->CenterX() - 100, window->CenterY() - 100);
	SmashValley::playerTwo->MoveTo(window->CenterX() + 100, window->CenterY() - 100);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	// sai com o pressionar do ESC
	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	// atualização da cena
	scene->Update();
	scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	// desenha pano de fundo
	//backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, bgScale);

	scene->Draw();

	/*if (SmashValley::viewBBox)*/
	scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	scene->Remove(SmashValley::playerOne, MOVING);
	scene->Remove(SmashValley::playerTwo, MOVING);

	delete scene;
	delete backg;
}


#include "Engine.h"
#include "SmashDragon.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

// ------------------------------------------------------------------------------

// inicializa membros est�ticos da classe
Game*		SmashDragon::level = nullptr;
Player*		SmashDragon::playerOne = nullptr;
Player*		SmashDragon::playerTwo = nullptr;
Audio*		SmashDragon::audio = nullptr;
bool		SmashDragon::viewBBox = false;
Character*	SmashDragon::characters[4] = { nullptr };
Sprite*		SmashDragon::charactersSelectImg[4] = { nullptr };
int			SmashDragon::playerOnePoints = 3;
int			SmashDragon::playerTwoPoints = 3;
bool		SmashDragon::passLevel = false;

// ------------------------------------------------------------------------------

void SmashDragon::Init()
{
	//ADICIONAR TODOS OS AUDIOS DO JOGO
	//audio = new Audio();
	//audio->Add(MENU, "Resources/Menu.wav");
	//audio->Add(MUSIC, "Resources/Music.wav");
	//audio->Add(TRANSITION, "Resources/Transition.wav");

	//ADICIONAR OS PERSONAGENS JOG�VEIS
	//characters[0] = new Character("Resources/..., ..., ...");
	//characters[1] = new Character("Resources/...");
	//characters[2] = new Character("Resources/...");
	//characters[3] = new Character("Resources/...");

	//ADICIONAR AS SEQU�NCIAS PARA CADA PERSONAGEM
	/*characters[0]->anim->Add(ATTACK, ..., ...);*/
	/*characters[0]->anim->Add(WALKLEFT, ..., ...);*/
	//...

	//ADICIONAR AS IMAGENS DE SELECAO DE PERSONAGEM JOG�VEIS
	//charactersSelectImg[0] = new Sprite("Resources/...");
	//charactersSelectImg[1] = new Sprite("Resources/...");
	//charactersSelectImg[2] = new Sprite("Resources/...");
	//charactersSelectImg[3] = new Sprite("Resources/...");

	viewBBox = false;

	//JOGADORES
	playerOne = new Player({ 'W', 'A', 'S', 'D', VK_SPACE, 'K', VK_SHIFT }, ONE);
	playerTwo = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2 }, TWO);

	level = new Home();
	level->Init();
}

// ------------------------------------------------------------------------------

void SmashDragon::Update()
{
	// habilita/desabilita visualiza��o da bounding box
	if (window->KeyPress('B'))
		viewBBox = !viewBBox;

	// atualiza n�vel
	level->Update();
}

// ------------------------------------------------------------------------------

void SmashDragon::Draw()
{
	// desenha n�vel
	level->Draw();
}

// ------------------------------------------------------------------------------

void SmashDragon::Finalize()
{
	level->Finalize();

	delete playerOne;
	delete playerTwo;
	delete audio;
	delete level;

	for (auto character : characters)
		delete character;

	for (auto charImg : charactersSelectImg)
		delete charImg;
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1200, 640);
	engine->window->Color(0, 0, 0);
    engine->window->Title("Smash Dragon");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new SmashDragon());

    delete engine;
    return status;
}


#include "Engine.h"
#include "SmashValley.h"

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game*		SmashValley::level = nullptr;
Player*		SmashValley::playerOne = nullptr;
Player*		SmashValley::playerTwo = nullptr;
Audio*		SmashValley::audio = nullptr;
bool		SmashValley::viewBBox = false;
Character*	SmashValley::characters[4] = { nullptr };
Sprite*		SmashValley::charactersSelectImg[4] = { nullptr };

// ------------------------------------------------------------------------------

void SmashValley::Init()
{
	//ADICIONAR TODOS OS AUDIOS DO JOGO
	//audio = new Audio();
	//audio->Add(MENU, "Resources/Menu.wav");
	//audio->Add(MUSIC, "Resources/Music.wav");
	//audio->Add(TRANSITION, "Resources/Transition.wav");

	//ADICIONAR OS PERSONAGENS JOGÁVEIS
	//characters[0] = new Character("Resources/..., ..., ...");
	//characters[1] = new Character("Resources/...");
	//characters[2] = new Character("Resources/...");
	//characters[3] = new Character("Resources/...");

	//ADICIONAR AS SEQUÊNCIAS PARA CADA PERSONAGEM
	/*characters[0]->anim->Add(ATTACK, ..., ...);*/
	/*characters[0]->anim->Add(WALKLEFT, ..., ...);*/
	//...

	//ADICIONAR AS IMAGENS DE SELECAO DE PERSONAGEM JOGÁVEIS
	//charactersSelectImg[0] = new Sprite("Resources/...");
	//charactersSelectImg[1] = new Sprite("Resources/...");
	//charactersSelectImg[2] = new Sprite("Resources/...");
	//charactersSelectImg[3] = new Sprite("Resources/...");

	viewBBox = false;

	//JOGADORES
	playerOne = new Player({ 'W', 'A', 'S', 'D', VK_SPACE, 'K', VK_SHIFT });
	playerTwo = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2 });

	// inicializa nível de abertura do jogo
	/*level = new Home();
	level->Init();*/
}

// ------------------------------------------------------------------------------

void SmashValley::Update()
{
	// habilita/desabilita visualização da bounding box
	if (window->KeyPress('B'))
		viewBBox = !viewBBox;

	// atualiza nível
	level->Update();
}

// ------------------------------------------------------------------------------

void SmashValley::Draw()
{
	// desenha nível
	level->Draw();
}

// ------------------------------------------------------------------------------

void SmashValley::Finalize()
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

// DESCOMENTAR PARA USAR ESSA CLASSE COMO ENTRADA DO JOGO

//int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//{
//    Engine* engine = new Engine();
//
//    // configura o motor
//    engine->window->Mode(WINDOWED);
//    engine->window->Size(600, 300);
//    engine->window->Color(30, 50, 80);
//    engine->window->Title("Gravity Guy");
//    engine->window->Icon(IDI_ICON);
//    engine->window->Cursor(IDC_CURSOR);
//    //engine->graphics->VSync(true);
//
//    // inicia o jogo
//    int status = engine->Start(new GravityGuy());
//
//    delete engine;
//    return status;
//}

// ----------------------------------------------------------------------------


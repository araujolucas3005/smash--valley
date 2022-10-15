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
Font*		SmashDragon::bold = nullptr;

// ------------------------------------------------------------------------------

void SmashDragon::Init()
{
	//ADICIONAR TODOS OS AUDIOS DO JOGO
	//audio = new Audio();
	//audio->Add(MENU, "Resources/Menu.wav");
	//audio->Add(MUSIC, "Resources/Music.wav");
	//audio->Add(TRANSITION, "Resources/Transition.wav");

	gohanLeft = new TileSet("Resources/gohan_spreadsheet.png", 172.877777, 159, 9, 117);
	gohanRight = new TileSet("Resources/gohan_spreadsheet_r.png", 172.877777, 159, 9, 117);

	kidGohanLeft = new TileSet("Resources/kid_gohan_sprite_sheet_l.png", 172, 144, 10, 140);
	kidGohanRight = new TileSet("Resources/kid_gohan_sprite_sheet_r.png", 172, 144, 10, 140);

	characters[0] = new Character(gohanLeft, gohanRight);
	characters[1] = new Character(gohanLeft, gohanRight);

	uint seqStill[10] = { 54, 55, 56, 57, 58, 58, 57, 56, 55, 54 };
	uint seqAttack[6] = { 18, 19, 20, 21, 22, 23 };
	uint seqHitTaken[2] = { 45 };
	uint seqJump[6] = { 65 };
	uint seqJumpUp[6] = { 65 };
	uint seqJumpDown[6] = { 68 };
	uint walk[6] = { 109 };
	uint seqDash[6] = { 81 };
	uint seqWalkJump[1] = { 67 };
	uint seqMovingAttack[6] = { 82, 82, 83, 83, 84, 84 };
	uint winnerEnd[6] = { 99, 100, 101, 102, 103, 104 };

	characters[0]->anim->Add(STILL, seqStill, 10);
	characters[0]->anim->Add(HIT, seqAttack, 6);
	characters[0]->anim->Add(HITTAKEN, seqHitTaken, 1);
	characters[0]->anim->Add(JUMP, seqJump, 1);
	characters[0]->anim->Add(WALKLEFT, walk, 1);
	characters[0]->anim->Add(DASH, seqDash, 1);
	characters[0]->anim->Add(WALKJUMP, seqWalkJump, 1);
	characters[0]->anim->Add(MOVINGATTACK, seqMovingAttack, 6);
	characters[0]->anim->Add(WINNEREND, seqMovingAttack, 6);
	characters[0]->anim->Add(JUMPUP, seqJumpUp, 1);
	characters[0]->anim->Add(JUMPDOWN, seqJumpDown, 1);

	characters[0]->animRight->Add(STILL, seqStill, 10);
	characters[0]->animRight->Add(HIT, seqAttack, 6);
	characters[0]->animRight->Add(HITTAKEN, seqHitTaken, 1);
	characters[0]->animRight->Add(JUMP, seqJump, 1);
	characters[0]->animRight->Add(WALKLEFT, walk, 1);
	characters[0]->animRight->Add(DASH, seqDash, 1);
	characters[0]->animRight->Add(WALKJUMP, seqWalkJump, 1);
	characters[0]->animRight->Add(MOVINGATTACK, seqMovingAttack, 6);
	characters[0]->animRight->Add(WINNEREND, seqMovingAttack, 6);
	characters[0]->animRight->Add(JUMPUP, seqJumpUp, 1);
	characters[0]->animRight->Add(JUMPDOWN, seqJumpDown, 1);

	uint kidGohanSeqStill[10] = { 1, 1, 1, 2, 3, 3, 2, 1, 1, 1 };
	uint kidGohanSeqAttack[6] = { 66, 66, 67, 67, 68, 68 };
	uint kidGohanSeqHitTaken[2] = { 45 };
	uint kidGohanSeqJump[6] = { 65 };
	uint kidGohanSeqJumpUp[6] = { 82 };
	uint kidGohanSeqJumpDown[6] = { 87 };
	uint kidGohanSeqWalk[6] = { 92 };
	uint kidGohanSeqDash[6] = { 60 };
	uint kidGohanSeqWalkJump[1] = { 83 };
	uint kidGohanSeqMovingAttack[6] = { 66, 66, 66, 67, 67, 67 };
	//uint kidGohanSeqWinnerEnd[6] = { 99, 100, 101, 102, 103, 104 };

	characters[1]->anim->Add(STILL, seqStill, 10);
	characters[1]->anim->Add(HIT, seqAttack, 6);
	characters[1]->anim->Add(HITTAKEN, seqHitTaken, 1);
	characters[1]->anim->Add(JUMP, seqJump, 1);
	characters[1]->anim->Add(WALKLEFT, walk, 1);
	characters[1]->anim->Add(DASH, seqDash, 1);
	characters[1]->anim->Add(WALKJUMP, seqWalkJump, 1);
	characters[1]->anim->Add(MOVINGATTACK, seqMovingAttack, 6);
	characters[1]->anim->Add(WINNEREND, seqMovingAttack, 6);
	characters[1]->anim->Add(JUMPUP, seqJumpUp, 1);
	characters[1]->anim->Add(JUMPDOWN, seqJumpDown, 1);

	characters[1]->animRight->Add(STILL, seqStill, 10);
	characters[1]->animRight->Add(HIT, seqAttack, 6);
	characters[1]->animRight->Add(HITTAKEN, seqHitTaken, 1);
	characters[1]->animRight->Add(JUMP, seqJump, 1);
	characters[1]->animRight->Add(WALKLEFT, walk, 1);
	characters[1]->animRight->Add(DASH, seqDash, 1);
	characters[1]->animRight->Add(WALKJUMP, seqWalkJump, 1);
	characters[1]->animRight->Add(MOVINGATTACK, seqMovingAttack, 6);
	characters[1]->animRight->Add(WINNEREND, seqMovingAttack, 6);
	characters[1]->animRight->Add(JUMPUP, seqJumpUp, 1);
	characters[1]->animRight->Add(JUMPDOWN, seqJumpDown, 1);

	// GOHAN PEQUENO
	//characters[1]->anim->Add(STILL, kidGohanSeqStill, 10);
	//characters[1]->anim->Add(HIT, kidGohanSeqAttack, 6);
	//characters[1]->anim->Add(HITTAKEN, kidGohanSeqHitTaken, 1);
	//characters[1]->anim->Add(JUMP, kidGohanSeqJump, 1);
	//characters[1]->anim->Add(WALKLEFT, kidGohanSeqWalk, 1);
	//characters[1]->anim->Add(DASH, kidGohanSeqDash, 1);
	//characters[1]->anim->Add(WALKJUMP, kidGohanSeqWalkJump, 1);
	//characters[1]->anim->Add(MOVINGATTACK, kidGohanSeqMovingAttack, 6);
	//characters[1]->anim->Add(JUMPUP, kidGohanSeqJumpUp, 1);
	//characters[1]->anim->Add(JUMPDOWN, kidGohanSeqJumpDown, 1);

	//characters[1]->animRight->Add(STILL, kidGohanSeqStill, 10);
	//characters[1]->animRight->Add(HIT, kidGohanSeqAttack, 6);
	//characters[1]->animRight->Add(HITTAKEN, kidGohanSeqHitTaken, 1);
	//characters[1]->animRight->Add(JUMP, kidGohanSeqJump, 1);
	//characters[1]->animRight->Add(WALKLEFT, kidGohanSeqWalk, 1);
	//characters[1]->animRight->Add(DASH, kidGohanSeqDash, 1);
	//characters[1]->animRight->Add(WALKJUMP, kidGohanSeqWalkJump, 1);
	//characters[1]->animRight->Add(MOVINGATTACK, kidGohanSeqMovingAttack, 6);
	//characters[1]->animRight->Add(JUMPUP, kidGohanSeqJumpUp, 1);
	//characters[1]->animRight->Add(JUMPDOWN, kidGohanSeqJumpDown, 1);

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

	bold = new Font("Resources/Tahoma14b.png");
	bold->Spacing("Resources/Tahoma14b.dat");

	viewBBox = false;

	//JOGADORES
	playerOne = new Player({ 'W', 'A', 'S', 'D', VK_SPACE, 'K', VK_SHIFT }, ONE, LEFT);
	playerTwo = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2 }, TWO, RIGHT);

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
	delete bold;
	delete gohanLeft;
	delete gohanRight;

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


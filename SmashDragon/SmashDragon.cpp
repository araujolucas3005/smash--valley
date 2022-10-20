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
TileSet*	SmashDragon::dash = nullptr;
TileSet*	SmashDragon::jump = nullptr;
TileSet*	SmashDragon::teleport = nullptr;
TileSet*	SmashDragon::hit = nullptr;
bool		SmashDragon::viewBBox = false;
Character*	SmashDragon::characters[4] = { nullptr };
Sprite*		SmashDragon::charactersSelectImg[4] = { nullptr };
Sprite*		SmashDragon::dragonballs[5] = { nullptr };
Sprite*		SmashDragon::shadow = nullptr;
int			SmashDragon::playerOnePoints = 3;
int			SmashDragon::playerTwoPoints = 3;
bool		SmashDragon::passLevel = false;
Font*		SmashDragon::bold = nullptr;
int			SmashDragon::round = 1;
// ------------------------------------------------------------------------------

void SmashDragon::Init()
{
	//ADICIONAR TODOS OS AUDIOS DO JOGO
	audio = new Audio();
	audio->Add(MENU, "Resources/Home/opening_song.wav");
	audio->Add(JUMPAUDIO, "Resources/jump.wav", 4);
	audio->Add(OUTOFSCREEN, "Resources/saiudatela.wav");
	audio->Add(PUNCH1, "Resources/punch1.wav");
	audio->Add(PUNCH2, "Resources/punch2.wav");
	audio->Add(L1THEME, "Resources/Stage1Theme.wav");
	audio->Add(L2THEME, "Resources/Stage2Theme.wav");
	audio->Add(L3THEME, "Resources/Stage3Theme.wav");
	audio->Add(KO, "Resources/KO.wav");
	audio->Add(FIGHT, "Resources/fight.wav");
	//audio->Add(MUSIC, "Resources/Music.wav");
	//audio->Add(TRANSITION, "Resources/Transition.wav");

	dragonballs[0] = new Sprite("Resources/db1.png");
	dragonballs[1] = new Sprite("Resources/db2.png");
	dragonballs[2] = new Sprite("Resources/db3.png");
	dragonballs[3] = new Sprite("Resources/db4.png");
	dragonballs[4] = new Sprite("Resources/db5.png");
	
	shadow = new Sprite("Resources/shadow.png");

	charactersSelectImg[0] = new Sprite("Resources/CharSelection/goku.png");
	charactersSelectImg[1] = new Sprite("Resources/CharSelection/gohan.png");
	charactersSelectImg[2] = new Sprite("Resources/CharSelection/vegeta.png");
	charactersSelectImg[3] = new Sprite("Resources/CharSelection/kid gohan.png");

	gokuLeft = new TileSet("Resources/goku_sprite_sheet_l.png", 153, 153, 8, 120);
	gokuRight = new TileSet("Resources/goku_sprite_sheet_r.png", 153, 153, 8, 112);

	gohanLeft = new TileSet("Resources/gohan_spreadsheet_l.png", 172.877777, 159, 9, 117);
	gohanRight = new TileSet("Resources/gohan_spreadsheet_r.png", 172.877777, 159, 9, 117);

	vegetaLeft = new TileSet("Resources/vegeta_spritesheet_l.png", 153, 150, 9, 126);
	vegetaRight = new TileSet("Resources/vegeta_spritesheet_r.png", 153, 150, 9, 126);

	kidGohanLeft = new TileSet("Resources/kid_gohan_sprite_sheet_l.png", 144, 172, 10, 140);
	kidGohanRight = new TileSet("Resources/kid_gohan_sprite_sheet_r.png", 144, 172, 10, 140);

	characters[0] = new Character(gokuLeft, gokuRight, charactersSelectImg[0]);
	characters[1] = new Character(gohanLeft, gohanRight, charactersSelectImg[1]);
	characters[2] = new Character(vegetaLeft, vegetaRight, charactersSelectImg[2]);
	characters[3] = new Character(kidGohanLeft, kidGohanRight, charactersSelectImg[3]);

	uint gseqStill[10] = { 0, 0, 1, 2, 3, 3, 2, 1, 0, 0 };
	uint gseqAttack[6] = { 96, 96, 96,  97, 97, 97 };
	uint gseqSpawn[6] = { 96, 96, 96,  97, 97, 97 };
	uint gseqHitTaken[4] = { 88, 87, 89, 90 };
	uint gseqJump[6] = { 64, 65, 66 };
	uint gseqJumpUp[3] = { 70, 70, 70 };
	uint gseqJumpDown[3] = { 64, 65, 66 };
	uint gwalk[2] = { 72, 73 };
	uint gseqDash[6] = { 24,25,56 };
	uint gseqWalkJump[1] = { 67 };
	uint gseqMovingAttack[6] = { 48, 49, 50, 51, 52, 53 };
	uint gwinnerEnd[6] = { 104, 104, 105, 105, 106, 106 };

	characters[0]->AddSec(STILL, gseqStill, 10);
	characters[0]->AddSec(HIT, gseqAttack, 6);
	characters[0]->AddSec(SPAWN, gseqSpawn, 6);
	characters[0]->AddSec(HITTAKEN, gseqHitTaken, 4);
	characters[0]->AddSec(JUMP, gseqJump, 1);
	characters[0]->AddSec(WALKLEFT, gwalk, 2);
	characters[0]->AddSec(DASH, gseqDash, 3);
	characters[0]->AddSec(WALKJUMP, gseqWalkJump, 1);
	characters[0]->AddSec(MOVINGATTACK, gseqMovingAttack, 6);
	characters[0]->AddSec(WINNEREND, gwinnerEnd, 6);
	characters[0]->AddSec(JUMPUP, gseqJumpUp, 3);
	characters[0]->AddSec(JUMPDOWN, gseqJumpDown, 3);

	//uint kidGohanSeqStill[10] = { 1, 1, 1, 2, 3, 3, 2, 1, 1, 1 };
	//uint kidGohanSeqAttack[6] = { 66, 66, 67, 67, 68, 68 };
	//uint kidGohanSeqHitTaken[2] = { 45 };
	//uint kidGohanSeqJump[6] = { 65 };
	//uint kidGohanSeqJumpUp[6] = { 82 };
	//uint kidGohanSeqJumpDown[6] = { 87 };
	//uint kidGohanSeqWalk[6] = { 92 };
	//uint kidGohanSeqDash[6] = { 60 };
	//uint kidGohanSeqWalkJump[1] = { 83 };
	//uint kidGohanSeqMovingAttack[6] = { 66, 66, 66, 67, 67, 67 };
	//uint kidGohanSeqWinnerEnd[6] = { 99, 100, 101, 102, 103, 104 };

	uint seqStill[10] = { 54, 55, 56, 57, 58, 58, 57, 56, 55, 54 };
	uint seqAttack[6] = { 18, 19, 20, 21, 22, 23 };
	uint seqSpawn[6] = { 18, 19, 20, 21, 22, 23 };
	uint seqHitTaken[2] = { 45 };
	uint seqJump[6] = { 65 };
	uint seqJumpUp[3] = { 63, 64, 65 };
	uint seqJumpDown[3] = { 66, 67, 68 };
	uint walk[2] = { 108, 109 };
	uint seqDash[6] = { 81 };
	uint seqWalkJump[1] = { 67 };
	uint seqMovingAttack[6] = { 82, 82, 83, 83, 84, 84 };
	uint winnerEnd[6] = { 99, 100, 101, 102, 103, 104 };

	characters[1]->AddSec(STILL, seqStill, 10);
	characters[1]->AddSec(HIT, seqAttack, 6);
	characters[1]->AddSec(SPAWN, seqSpawn, 6);
	characters[1]->AddSec(HITTAKEN, seqHitTaken, 1);
	characters[1]->AddSec(JUMP, seqJump, 1);
	characters[1]->AddSec(WALKLEFT, walk, 2);
	characters[1]->AddSec(DASH, seqDash, 1);
	characters[1]->AddSec(WALKJUMP, seqWalkJump, 1);
	characters[1]->AddSec(MOVINGATTACK, seqMovingAttack, 6);
	characters[1]->AddSec(WINNEREND, winnerEnd, 6);
	characters[1]->AddSec(JUMPUP, seqJumpUp, 3);
	characters[1]->AddSec(JUMPDOWN, seqJumpDown, 3);

	uint vseqStill[10] = { 0, 0, 1, 2, 3, 3, 2, 1, 0, 0 };
	uint vseqAttack[6] = { 90, 91, 92, 92, 93, 94 };
	uint vseqSpawn[6] = { 90, 91, 92, 92, 93, 94 };
	uint vseqHitTaken[4] = { 36, 37, 38, 39 };
	uint vseqJump[6] = { 64, 65, 66 };
	uint vseqJumpUp[3] = { 72, 73, 74 };
	uint vseqJumpDown[3] = { 77, 78, 78 };
	uint vwalk[2] = { 81, 82 };
	uint vseqDash[6] = { 54 };
	uint vseqWalkJump[1] = { 67 };
	uint vseqMovingAttack[6] = { 54, 55, 56, 57, 58, 59 };
	uint vwinnerEnd[9] = { 117, 118, 119, 120, 121, 122, 123, 124, 125 };

	characters[2]->AddSec(STILL, vseqStill, 10);
	characters[2]->AddSec(HIT, vseqAttack, 6);
	characters[2]->AddSec(SPAWN, vseqSpawn, 6);
	characters[2]->AddSec(HITTAKEN, vseqHitTaken, 1);
	characters[2]->AddSec(JUMP, vseqJump, 1);
	characters[2]->AddSec(WALKLEFT, vwalk, 2);
	characters[2]->AddSec(DASH, vseqDash, 1);
	characters[2]->AddSec(WALKJUMP, vseqWalkJump, 1);
	characters[2]->AddSec(MOVINGATTACK, vseqMovingAttack, 6);
	characters[2]->AddSec(WINNEREND, vwinnerEnd, 9);
	characters[2]->AddSec(JUMPUP, vseqJumpUp, 3);
	characters[2]->AddSec(JUMPDOWN, vseqJumpDown, 3);

	uint kgseqStill[10] = { 0, 0, 1, 2, 3, 3, 2, 1, 0, 0 };
	uint kgseqAttack[6] = { 120, 121, 122,122, 123, 124 };
	uint kgseqSpawn[6] = { 120, 121, 122,122, 123, 124 };
	uint kgseqHitTaken[4] = { 40, 41, 42, 43 };
	uint kgseqJump[6] = { 64, 65, 66 };
	uint kgseqJumpUp[3] = { 80, 81, 82 };
	uint kgseqJumpDown[3] = { 83, 84, 85 };
	uint kgwalk[2] = { 90, 91 };
	uint kgseqDash[6] = { 62 };
	uint kgseqWalkJump[1] = { 67 };
	uint kgseqMovingAttack[6] = { 60, 61, 62, 63, 64, 65 };
	uint kgwinnerEnd[10] = { 130, 131, 132, 133, 134, 135, 136, 137, 138, 139 };

	characters[3]->AddSec(STILL, kgseqStill, 10);
	characters[3]->AddSec(HIT, kgseqAttack, 6);
	characters[3]->AddSec(SPAWN, kgseqSpawn, 6);
	characters[3]->AddSec(HITTAKEN, kgseqHitTaken, 1);
	characters[3]->AddSec(JUMP, kgseqJump, 1);
	characters[3]->AddSec(WALKLEFT, kgwalk, 2);
	characters[3]->AddSec(DASH, kgseqDash, 1);
	characters[3]->AddSec(WALKJUMP, kgseqWalkJump, 1);
	characters[3]->AddSec(MOVINGATTACK, kgseqMovingAttack, 6);
	characters[3]->AddSec(WINNEREND, kgwinnerEnd, 10);
	characters[3]->AddSec(JUMPUP, kgseqJumpUp, 3);
	characters[3]->AddSec(JUMPDOWN, kgseqJumpDown, 3);


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


	bold = new Font("Resources/Tahoma14b.png");
	bold->Spacing("Resources/Tahoma14b.dat");

	viewBBox = false;

	// Add desenho da vida
	characters[0]->hpImg = new Sprite("Resources/hp_goku.png");
	characters[1]->hpImg = new Sprite("Resources/hp_gohan.png");
	characters[2]->hpImg = new Sprite("Resources/hp_vegeta.png");
	characters[3]->hpImg = new Sprite("Resources/hp_kgohan.png");

	// Add sprites dos personagens para transicao de tela
	characters[0]->charImgTransition = new Sprite("Resources/gokuright.png");
	characters[1]->charImgTransition = new Sprite("Resources/gohanrightt.png");
	characters[2]->charImgTransition = new Sprite("Resources/vegitaright.png");
	characters[3]->charImgTransition = new Sprite("Resources/kgohanrigiht.png");

	//JOGADORES
	playerOne = new Player({ 'W', 'A', 'S', 'D', VK_SPACE, 'K', VK_SHIFT }, ONE, LEFT);
	playerTwo = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2 }, TWO, RIGHT);

	hit = new TileSet("Resources/strong_hit_sprite_small.png", 1, 4);
	jump = new TileSet("Resources/jump_straight_sprite.png", 1, 6);
	dash = new TileSet("Resources/dash_sprite_small.png", 1, 6);
	teleport = new TileSet("Resources/teleport.png", 8, 8);

	level = new Home();
	SmashDragon::audio->Play(MENU, true);
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
	delete kidGohanLeft;
	delete kidGohanRight;
	delete gokuLeft;
	delete gokuRight;
	delete vegetaLeft;
	delete vegetaRight;
	delete hit;
	delete dash;
	delete jump;
	delete teleport;

	for (auto character : characters)
		delete character;

	for (auto charImg : charactersSelectImg)
		delete charImg;

	for (auto dragonball : dragonballs)
		delete dragonball;
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


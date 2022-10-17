#ifndef _SMASH_DRAGON_H_
#define _SMASH_DRAGON_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Sprite.h"
#include "Character.h"
#include "Resources.h"
#include "Font.h"

enum Sounds { MENU, MUSIC, TRANSITION, GET_READY_FOR_BATTLE };

class SmashDragon : public Game
{
private:

public:
	static Game* level;            // n�vel atual do jogo
	static Player* playerOne;
	static Player* playerTwo;
	static Audio* audio;           // sistema de �udio
	static bool viewBBox;           // estado da bounding box
	static Character* characters[4];
	static Sprite* charactersSelectImg[4];
	static int playerOnePoints;
	static int playerTwoPoints;
	static bool passLevel;

	static TileSet* hit;
	static TileSet* dash;
	static TileSet* jump;

	TileSet* gokuRight;
	TileSet* gokuLeft;

	TileSet* vegetaRight;
	TileSet* vegetaLeft;

	TileSet* gohanLeft;
	TileSet* gohanRight;

	TileSet* kidGohanLeft;
	TileSet* kidGohanRight;

	static Font* bold;

	void Init();                    // inicializa jogo
	void Update();                  // atualiza l�gica do jogo
	void Draw();                    // desenha jogo
	void Finalize();                // finaliza jogo

	template<class T>
	static void NextLevel()         // muda para pr�ximo n�vel do jogo
	{
		if (level)
		{
			level->Finalize();
			delete level;
			level = new T();
			level->Init();
		}
	};
};

#endif
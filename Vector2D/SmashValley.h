#ifndef _SMASH_VALLEY_H_
#define _SMASH_VALLEY_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Sprite.h"
#include "Character.h"
#include "Resources.h"

enum Sounds { MENU, MUSIC, TRANSITION };

class SmashValley : public Game
{
private:
	static Game* level;            // nível atual do jogo

public:
	static Player* playerOne;
	static Player* playerTwo;
	static Audio* audio;           // sistema de áudio
	static bool viewBBox;           // estado da bounding box
	static Character* characters[4];
	static Sprite* charactersSelectImg[4];

	void Init();                    // inicializa jogo
	void Update();                  // atualiza lógica do jogo
	void Draw();                    // desenha jogo
	void Finalize();                // finaliza jogo

	template<class T>
	static void NextLevel()         // muda para próximo nível do jogo
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
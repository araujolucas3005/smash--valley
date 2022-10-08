/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo SVW
//
**********************************************************************************/

#ifndef _SVW_PLAYER_H_
#define _SVW_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Image.h"
#include "Scene.h"
#include "Timer.h"
#include "string"
#include "Audio.h"
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados possíveis para o jogador

enum PLAYERSTATE { STOPED, UP, DOWN, LEFT, RIGHT };

struct MovementKeys {
	int up;
	int left;
	int down;
	int right;
	int jump;
};

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	Sprite* spriteL = nullptr;         // sprite do player indo para esquerda
	Sprite* spriteR = nullptr;         // sprite do player indo para direita
	Sprite* spriteU = nullptr;         // sprite do player indo para cima
	Sprite* spriteD = nullptr;         // sprite do player indo para baixo
	Sprite* currSprite = nullptr;

	float width;
	float height;

	bool ctrlJump = true;
	bool onAir = false;
	ushort jumps = 0;

	float velX = 0;                     // velocidade horizontal do player
	float velY = 0;                     // velocidade vertical do player

	Timer* jumpTimer = nullptr;

	MovementKeys movementKeys;

public:
	Player(MovementKeys movementKeys);
	~Player();                          // destrutor

	void Stop();                        // pára jogador
	void Up();                          // muda direção para cima
	void Down();                        // muda direção para baixo
	void Left();                        // muda direção para esquerda
	void Right();                       // muda direção para direita

	void OnCollision(Object* obj);     // resolução da colisão

	void Update();                      // atualização do objeto
	void Draw();                        // desenho do objeto
};

#endif
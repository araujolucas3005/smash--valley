#include "LevelAnim.h"
#include "SmashDragon.h"
#include "Level.h"

LevelAnim::LevelAnim(TileSet* tileset, float delay, bool repeat) {
	ts = tileset;
	this->repeat = repeat;
	anim = new Animation(tileset, delay, repeat);
}

LevelAnim::~LevelAnim() {
	delete anim;
}

void LevelAnim::OnCollision(Object* obj) {}

void LevelAnim::Update() {
	if (anim->Inactive() && !repeat) {
		Level* level = (Level*) SmashDragon::level;
		level->scene->Delete(this, STATIC);
	}
	else {
		anim->NextFrame();
	}

}

inline void LevelAnim::Draw() { anim->Draw(x, y, Layer::FRONT); }
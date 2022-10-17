#include "Object.h"
#include "TileSet.h"
#include "Animation.h"

class LevelAnim : public Object
{
private:
    Animation* anim = nullptr;
    TileSet* ts = nullptr;

    bool repeat;

public:
    LevelAnim(TileSet* tileset, float delay, bool repeat = false);                           // construtor
    ~LevelAnim();                          // destrutor

    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};
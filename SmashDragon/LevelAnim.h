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

    void OnCollision(Object* obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};
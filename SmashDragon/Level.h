#ifndef _SMASH_DRAGON_LEVEL_H_
#define _SMASH_DRAGON_LEVEL_H_

#include "Scene.h"
#include "Timer.h"

class Level
{
private:

public:
    static Scene* scene;               // gerenciador de cena 
    bool ended = false;
    Timer* levelEndingTimer = nullptr;
};

// ---------------------------------------------------------------------------------

#endif
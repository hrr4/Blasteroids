#ifndef LEVEL_H
#define LEVEL_H

#include "gamescreen.h"
#include "player.h"
#include "fontengine.h"
#include "comet.h"
#include "Projectile.h"
#include "starfield.h"
#include "icollide.h"
#include <vector>
#include <SDL_ttf.h>

class Level : public IGameScreen {
public:
    Level(int levelNum);
    virtual ~Level();
    virtual void Logic();
    virtual void Draw();
    virtual void Handle_Events();
private:
    FontEngine* fe;
    Entity* starfield, *testProj;
    ICollide* iCollide;
    std::vector<Player*> playerVec;
    std::vector<Collider*> projVec, cometVec; 
	std::vector<Collider*>::iterator it;
	std::vector<Player*>::iterator pIt;
    int untilNext, kills;
};

#endif
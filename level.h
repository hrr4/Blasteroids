#ifndef LEVEL_H
#define LEVEL_H

#include "gamescreen.h"
#include "player.h"
#include "comet.h"
#include "Projectile.h"
#include "starfield.h"
#include "icollide.h"
#include "hud.h"
#include <vector>

class Level : public IGameScreen {
public:
    Level(int levelNum);
    virtual ~Level();
    virtual void Logic();
    virtual void Draw();
    virtual void Handle_Events();
private:
    Entity* starfield;
    ICollide* iCollide;
    HUD* hud;
    std::vector<Player*> playerVec;
    std::vector<Collider*> projVec, cometVec; 
	std::vector<Collider*>::iterator it;
	std::vector<Player*>::iterator pIt;
    int untilNext, kills, score;
};

#endif
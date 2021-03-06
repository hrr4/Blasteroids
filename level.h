#ifndef LEVEL_H
#define LEVEL_H

#include "gamescreen.h"
#include "player.h"
#include "comet.h"
#include "Projectile.h"
#include "starfield.h"
#include "icollide.h"
#include "hud.h"
#include "IParticle.h"
#include <string>
#include <vector>

class Level : public IGameScreen {
public:
    Level(int _levelNum);
    virtual ~Level();
    virtual void Logic();
    virtual void Draw();
    virtual void Handle_Events();
private:
    void ScoreIncrease();
    Vectorf randOutside(float _xMax, float _yMax, float _min, float _dist);
    void createCometChild(Vectorf& _parentVec, int _n);

    Starfield stars;
    ICollide* iCollide;
    HUD* hud;
    Player* mainPlayer;
    IParticle particleEngine;
    std::vector<Collider*> projVec; 
    std::vector<Comet*> cometVec; 
    unsigned int numPoints, untilNext, kills, announceSize, levelNum, cometScore, cometSpawn;
    bool callAnnouncement; 
    static int playerLives, score;
};

#endif

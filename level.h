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
    void Tutorial();
    void ScoreIncrease();
    float randOutside(float _first, float _second, float _distance);
private:
    Starfield stars;
    ICollide* iCollide;
    HUD* hud;
    Player* mainPlayer;
    IParticle particleEngine; // JUST FOR TESTING PURPOSES, THIS MIGHT NEED TO BE A SINGLETON LATER
    std::vector<Collider*> projVec; 
    std::vector<Comet*> cometVec; 
	std::vector<Collider*>::iterator it;
	std::vector<Comet*>::iterator cIt;
    int untilNext, kills, announceSize, levelNum, cometScore, cometSpawn, playerRespawn;
    bool callAnnouncement; 
    static bool finishTutorial;
    static int playerLives, score/*, playerRespawn*/;
};

#endif

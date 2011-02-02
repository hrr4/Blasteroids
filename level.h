#ifndef LEVEL_H
#define LEVEL_H

#include "gamescreen.h"
#include "player.h"
#include "comet.h"
#include "Projectile.h"
#include "starfield.h"
#include "icollide.h"
#include "hud.h"
//#include "emitter.h"
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
    void ScoreDraw(int& score);
private:
    Starfield stars;
    ICollide* iCollide;
    HUD* hud;
    //Emitter cometEmitter;
    std::vector<Player*> playerVec;
    std::vector<Collider*> projVec; 
    std::vector<Comet*> cometVec; 
	std::vector<Collider*>::iterator it;
	std::vector<Player*>::iterator pIt;
	std::vector<Comet*>::iterator cIt;
    int untilNext, kills, announceSize, levelNum, cometScore, cometSpawn;
    bool callAnnouncement, callCometScore; 
    static bool finishTutorial;
    static int playerLives, score;
    //std::vector<Collider*> testVec;
};

#endif
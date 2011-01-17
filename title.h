#ifndef TITLE_H
#define TITLE_H

#include "gamescreen.h"
//#include "OGLFT.h"
#include "player.h"
#include "comet.h"
#include "Projectile.h"
#include "starfield.h"
#include "icollide.h"
#include <vector>
#include <SDL_ttf.h>
#include <boost\smart_ptr\shared_ptr.hpp>

class Title : public IGameScreen {
public:
    Title();
    virtual ~Title();
    virtual void Logic();
    virtual void Draw();
    virtual void Handle_Events();
	bool PushCollider(Entity* Entity);
	bool PopCollider(Entity* Entity);
private:
    TTF_Font* f_Title, *f_Banner;
    SDL_Rect r_Title, r_NewButton, r_HScore, r_Options, r_QuitButton, r_Selector;
    SDL_Surface* s_Title, *s_NewButton, *s_QuitButton, *s_HScore, *s_Options, *s_Selector;
    Entity* starfield, *testProj;
    Player* player;
    ICollide* iCollide;
    SDL_Color col_Grey, col_White;
    std::vector<Collider*> projVec, cometVec;
	//std::vector<boost::shared_ptr<Collider> > projVec, cometVec;
    //OGLFT::Monochrome* face;
};
#endif

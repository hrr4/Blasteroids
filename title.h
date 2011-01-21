#ifndef TITLE_H
#define TITLE_H

#include "gamescreen.h"
#include "fontengine.h"
#include "starfield.h"
//#include <SDL_ttf.h>

class Title : public IGameScreen {
public:
    Title();
    virtual ~Title();
    virtual void Logic();
    virtual void Draw();
    virtual void Handle_Events();
    void DrawMenu();
private:
    FontEngine* fe, *TEST;
    Entity* starfield;
    int selectorX, selectorY;
};
#endif

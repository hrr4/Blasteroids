#ifndef TITLE_H
#define TITLE_H

#include "gamescreen.h"
#include "fontengine.h"
#include "starfield.h"

class Title : public IGameScreen {
public:
    Title();
    virtual ~Title();
    virtual void Logic();
    virtual void Draw();
    virtual void Handle_Events();
    void DrawMain();
    void DrawScores();
    void DrawOptions();
private:
    enum Screen {Main, Scores, Options};
    Screen activeScreen;
    FontEngine* fe;
    Entity* starfield;
    int selectorX, selectorY;
};
#endif
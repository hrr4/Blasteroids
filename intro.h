#ifndef INTRO_H
#define INTRO_H

#include "gamescreen.h"
#include "surface.h"

class Intro : public IGameScreen {
public:
	Intro();
	virtual ~Intro();
	virtual void Logic();
	virtual void Handle_Events();
	virtual void Draw();
private:
	SDL_Surface* s_Background;
};

#endif
#ifndef IGAMESTATE_H
#define IGAMESTATE_H

#include <SDL_image.h>
#include "surface.h"
#include "event.h"
#include <random>
#include <time.h>
#include "statemanager.h"
#include "fontengine.h"
#include <memory>

class IGameScreen {
public:
	IGameScreen();
	virtual ~IGameScreen();
	StateManager::Child Get_State();
	virtual void Logic()=0;
	virtual void Handle_Events()=0;
	virtual void Draw()=0;

protected:
    FontEngine* fe;
    //boost::shared_ptr<FontEngine> fe;
    //std::shared_ptr<FontEngine> fe;
    //FontEngine* fe_p;
	void Set_State(StateManager::Child tempChild);
	StateManager::Child currentChild;
};

#endif
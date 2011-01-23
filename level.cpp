#include "level.h"

Level::Level(int levelNum) : kills(0), score(0) {
	iCollide = new ICollide();
	starfield = new Starfield();
    hud = new HUD(fe, true, true, true);
	projVec.reserve(5);
	cometVec.reserve(5);
    playerVec.reserve(2);    playerVec.push_back(new Player(iCollide, 400, 300, 25, 25));
//    untilNext = (levelNum + 10)*(levelNum+5);
    untilNext = 2;
}

Level::~Level() {
    projVec.clear();
    playerVec.clear();
    cometVec.clear();
    delete iCollide;
    delete starfield;
    delete hud;
}

void Level::Draw() {	if (!playerVec.empty()) {
        for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        	(*pIt)->Draw();
            hud->Thrust((*pIt)->GetPosition().x(), (*pIt)->GetPosition().y()-25,
                (*pIt)->GetThrust(), 1);
        }
    }
	starfield->Draw();
	if (!cometVec.empty()) {
        for (it = cometVec.begin(); it != cometVec.end(); ++it) {
    		(*it)->Draw();
        }
	}
	if (!projVec.empty()) {
        for (it = projVec.begin(); it != projVec.end(); ++it) {
    		(*it)->Draw();
        }
	}
    hud->Score(score);
}

void Level::Handle_Events() {
    while(SDL_PollEvent(Event::Get_Event())) {
		if (Event::Get_Event()->type == SDL_QUIT) {
			Set_State(StateManager::Child_Quit);
		} else if (Event::Get_Event()->type == SDL_KEYDOWN) {
			switch (Event::Get_Event()->key.keysym.sym) {
                case SDLK_ESCAPE : 
						Set_State(StateManager::Child_Quit);
                        break;
            	case SDLK_SPACE:
                    	if (!playerVec.empty()) {
                            for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        						if ((*pIt)->CanShoot()) {
        							projVec.push_back(new Projectile(Projectile::PROJ_BASIC, iCollide,
        								(*pIt)->GetPosition().x()+sinf((*pIt)->GetAngle()), 
        								(*pIt)->GetPosition().y()+cosf((*pIt)->GetAngle()),
        								(*pIt)->GetAngle()));
        							(*pIt)->Shoot();
        						}
                            }
                        }
            			break;
            	case SDLK_c:
                    	if (!playerVec.empty()) {
                            for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        						cometVec.push_back(new Comet(iCollide, 300, 300, (rand() % 50+60), (rand() % 50+60), 
                                    (rand() % 3 + 5), 5, (*pIt)->GetPosition()));
                            }
                        }
            			break;
                case SDLK_m:
                    hud->Announcement("TESTZ0RZ!", Window::Get_Surf()->w/2, Window::Get_Surf()->h/2, 10, 60);
           }
		}
	}
	if (!playerVec.empty()) {
        for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        	(*pIt)->Handle_Events();
        }
    }
}

void Level::Logic() {	starfield->Logic();
	if (!playerVec.empty()) {
        for (pIt = playerVec.begin(); pIt != playerVec.end();) {
            if ((*pIt)->GetAlive()) {
        		(*pIt)->Logic();
                ++pIt;
    		} else {
                delete *pIt;
                pIt = playerVec.erase(pIt);
                if (pIt != playerVec.end()) {
                    ++pIt;
                }
            }
        }
	}
	if (!cometVec.empty()) {
        for (it = cometVec.begin(); it != cometVec.end();) {
            if ((*it)->GetAlive()) {
        		(*it)->Logic();
                ++it;
    		} else {
                delete *it;
                ++kills;
                ++score;
               it = cometVec.erase(it);
                if (it != cometVec.end()) {
                    ++it;
                }
            }
        }
	}
	if (!projVec.empty()) {
        for (it = projVec.begin(); it != projVec.end();) {
            if ((*it)->GetAlive()) {
        		(*it)->Logic();
                ++it;
			} else {
                delete *it;
                it = projVec.erase(it);
                if (it != projVec.end()) {
                    ++it;
                }
            }
        }
    }

    // Switch Level Logic
    if (kills == untilNext) {
        Set_State(StateManager::Child_Success);
    }

}
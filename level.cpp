#include "level.h"

Level::Level(int _levelNum) : kills(0), score(0), callAnnouncement(false),
    announceSize(60), levelNum(_levelNum) {
	iCollide = new ICollide();
	stars = Starfield();
    hud = new HUD(fe, true, true, true);
	projVec.reserve(5);
	cometVec.reserve(20);
    playerVec.reserve(2);    playerVec.push_back(new Player(iCollide, 320, 240, 25, 25));
    untilNext = (levelNum + (rand() % 1 + 9))*(levelNum + (rand() % 1 + 15));
}

Level::~Level() {
    projVec.clear();
    playerVec.clear();
    cometVec.clear();
    delete iCollide;
    delete hud;
}

void Level::Draw() {	if (!playerVec.empty()) {
        for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        	(*pIt)->Draw();
            hud->Thrust((*pIt)->GetPosition().x(), (*pIt)->GetPosition().y()-25,
                (*pIt)->GetThrust(), 1);
        }
    }
	stars.Draw();
	if (!cometVec.empty()) {
        for (cIt = cometVec.begin(); cIt != cometVec.end(); ++cIt) {
    		(*cIt)->Draw();
        }
	}
	if (!projVec.empty()) {
        for (it = projVec.begin(); it != projVec.end(); ++it) {
    		(*it)->Draw();
        }
	}
    hud->Score(score, 0, 10);
    if (callAnnouncement) {
        hud->Announcement("TESTZ0RZ!", "04b_11", 
            Window::Get_Surf()->w/2, Window::Get_Surf()->h/2, announceSize);
    }
}

void Level::Handle_Events() {
    while(SDL_PollEvent(Event::Get_Event())) {
		if (Event::Get_Event()->type == SDL_QUIT) {
			Set_State(StateManager::Child_Quit);
		} else if (Event::Get_Event()->type == SDL_KEYDOWN) {
			switch (Event::Get_Event()->key.keysym.sym) {
                case SDLK_ESCAPE : 
                        Set_State(StateManager::Child_Exit);
                        break;
            	case SDLK_SPACE:
                    	if (!playerVec.empty()) {
                            for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        						if ((*pIt)->CanShoot()) {
        							projVec.push_back(new Projectile(Projectile::PROJ_BASIC, iCollide,
                                        (*pIt)->GetSpeed(), (*pIt)->GetPosition().x()+sinf((*pIt)->GetAngle()), 
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
        						cometVec.push_back(new Comet(iCollide, 300.0f, 300.0f, 
                                    static_cast<float>(rand() % 50+60), static_cast<float>(rand() % 50+60), 
                                    (rand() % 3 + 5), 5, (*pIt)->GetPosition()));
                            }
                        }
            			break;
                case SDLK_m:
                    callAnnouncement = true;
                    break;
                case SDLK_s:
                	if (playerVec.empty()) {
                        playerVec.push_back(new Player(iCollide, 400, 300, 25, 25));
                    }
                    break;
                case SDLK_t:
                	if (!playerVec.empty()) {
                        for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
                            cometVec.push_back(new Comet(iCollide, -20.0f, -10.0f, 
                                static_cast<float>(rand() % 50+60), static_cast<float>(rand() % 50+60), 
                                (rand() % 3 + 5), 5, (*pIt)->GetPosition()));
                        }
                    }
        			break;
           }
		}
	}
	if (!playerVec.empty()) {
        for (pIt = playerVec.begin(); pIt != playerVec.end(); ++pIt) {
        	(*pIt)->Handle_Events();
        }
    }
}

void Level::Logic() {	if (!playerVec.empty()) {
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
        for (cIt = cometVec.begin(); cIt != cometVec.end();) {
            if ((*cIt)->GetAlive()) {
        		(*cIt)->Logic();
                // Check bounds, set to wrap
                if (((*cIt)->GetPosition().x() > 0 && (*cIt)->GetPosition().x() < Window::Get_Surf()->w) &&
                    ((*cIt)->GetPosition().y() > 0 && (*cIt)->GetPosition().y() < Window::Get_Surf()->h)) {
                        (*cIt)->SetWrap(true);
                }
                ++cIt;
    		} else {
                delete *cIt;
                ++kills;
                ++score;
               cIt = cometVec.erase(cIt);
                if (cIt != cometVec.end()) {
                    ++cIt;
                }
            }
        }
	}
	if (!projVec.empty()) {
        for (it = projVec.begin(); it != projVec.end();) {
            if ((*it)->GetAlive() && 
                !((*it)->GetPosition().x() < -20 || (*it)->GetPosition().x() > Window::Get_Surf()->w+20 || 
                    (*it)->GetPosition().y() < -20 || (*it)->GetPosition().y() > Window::Get_Surf()->h+20)) {
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
    /*if (kills == untilNext) {
        Set_State(StateManager::Child_Success);
    }*/

}
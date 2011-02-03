#include "level.h"

bool Level::finishTutorial = false;
int Level::playerLives = 3;
int Level::score = 0;

Level::Level(int _levelNum) : kills(0), callAnnouncement(true), callCometScore(false), announceSize(90), levelNum(_levelNum), 
    stars(Starfield()), iCollide(new ICollide()), hud(new HUD(fe, true, true, true)), cometSpawn(SDL_GetTicks()+2000), playerRespawn(SDL_GetTicks()+2000) {
    playerVec.push_back(new Player(iCollide, 320, 240, 25, 25));
    untilNext = (levelNum + (rand() % 1 + 3))*(levelNum + (rand() % 1 + 3));
    if (levelNum == 1) {
        playerLives = 3;
        score = 0;
    }
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
            hud->Thrust((*pIt)->GetPosition().x(), (*pIt)->GetPosition().y()-25, (*pIt)->GetThrust(), 1);
            if (levelNum == 0 && !finishTutorial) {
                Tutorial();
            }            /*if ((untilNext - kills) <= 10) {
                std::string remaining = itos(untilNext-kills)+" Remaining";
                hud->Status(remaining ,"FreeSans", (*pIt)->GetPosition().x()-40, 
                    (*pIt)->GetPosition().y()-40, 13, 3);
            }*/            if (callCometScore) {
                int interval = 10;
                int timeout = SDL_GetTicks() + interval;
                cometScore = (rand() % 20);
                std::string wtf2 = ("+" + itos(cometScore));
                /*hud->Status(wtf2.c_str(),"FreeSans", (*pIt)->GetPosition().x()-40, 
                    (*pIt)->GetPosition().y()-40, 13, 3);*/
                //callCometScore = false;
            }
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
    hud->Simple(score, 0, 10);
    hud->Simple(untilNext-kills, (Window::Get_Surf()->w/2), 10);
    if (callAnnouncement) {
        hud->Announcement(itos(levelNum).c_str(), "04b_11", 
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
                                    (rand() % 3 + 5), levelNum + (rand() % 1 + 3), (*pIt)->GetPosition()));
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
                                (rand() % 3 + 5), levelNum + (rand() % 1 + 3), (*pIt)->GetPosition()));
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

void Level::Logic() {

	if (!playerVec.empty()) {
        for (pIt = playerVec.begin(); pIt != playerVec.end();) {
            if ((*pIt)->GetAlive()) {
        		(*pIt)->Logic();
                if (SDL_GetTicks() > cometSpawn) {
                    cometVec.push_back(new Comet(iCollide, randOutside(0.0f, static_cast<float>(Window::Get_Surf()->w), 20.0f), 
					    randOutside(0.0f,  static_cast<float>(Window::Get_Surf()->h), 20.0f), 
					static_cast<float>(rand() % 50+60), static_cast<float>(rand() % 50+60), (rand() % 3 + 5),  
					static_cast<float>((levelNum/10) + (Utility::UGen_Random(0.1, 1.0))), 
					(*pIt)->GetPosition()));
                    cometSpawn = SDL_GetTicks() + 2000;
                }
                ++pIt;
    		} else {
			if (SDL_GetTicks() > playerRespawn) {
				if (playerLives != 0) {
				    playerLives--;
				    playerVec.push_back(new Player(iCollide, 320, 240, 25, 25));
				    playerRespawn = SDL_GetTicks() + 2000;
				} else {
				    Set_State(StateManager::Child_Exit);
				}
			} else {

				delete *pIt;
				pIt = playerVec.erase(pIt);
				if (pIt != playerVec.end()) {
				    ++pIt;
				}
			}
            /*} else {
                delete *pIt;
                pIt = playerVec.erase(pIt);
                if (pIt != playerVec.end()) {
                    ++pIt;
                }*/
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
                score += cometScore;
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
                !((*it)->GetPosition().x() < -10 || (*it)->GetPosition().x() > Window::Get_Surf()->w+10 || 
                    (*it)->GetPosition().y() < -10 || (*it)->GetPosition().y() > Window::Get_Surf()->h+10)) {
        		(*it)->Logic();
                ++it;
			} else {
                delete *it;
                callCometScore = true;
                it = projVec.erase(it);
                if (it != projVec.end()) {
                    ++it;
                }
            }
        }
    }

    // Switch Level
    if (kills == untilNext) {
        Set_State(StateManager::Child_Success);
    }
}

void Level::Tutorial() {
    const std::string tutText = "Welcome to Blasteroids!\n"
                                "Looks like it's your first time!\n"
                                "It's pretty simple really.....\n"
                                "Shoot Asteroids, get Points!\n"
                                "You get bombs to play with as well\n"
                                "If you run out of lives...well I think you know\n"
                                "Have fun!\n";
    /*hud->Status(tutText.c_str() ,"FreeSans", (*pIt)->GetPosition().x()-40, 
        (*pIt)->GetPosition().y()-40, 13, 3);*/
    //finishTutorial = true;
}

/*void Level::CometScore() {
    hud->Status(itos(,"FreeSans", (*pIt)->GetPosition().x()-40, 
        (*pIt)->GetPosition().y()-40, 13, 3);
  */  

float Level::randOutside(float _first, float _second, float _distance) {
    int test = Utility::UGen_Random(_first, _second);
    if (test <= (_second-_first)/2) {
        return Utility::UGen_Random((_first-_distance), _first);
    } else {
        return Utility::UGen_Random((_second-_distance), _second);
    }
}

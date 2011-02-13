#include "level.h"

bool Level::finishTutorial = false;
int Level::playerLives = 3;
int Level::score = 0;

Level::Level(int _levelNum) : kills(0), callAnnouncement(true), announceSize(90), 
	levelNum(_levelNum), stars(Starfield()), iCollide(new ICollide()), 
	hud(new HUD(fe, true, true, true)), cometSpawn(SDL_GetTicks()+5000), 
	playerRespawn(SDL_GetTicks()+5000) {
	mainPlayer = new Player(iCollide, 320, 240, 25, 25);
	untilNext = (levelNum + (rand() % 1 + 3))*(levelNum + (rand() % 1 + 3));
	if (levelNum == 1) {
		Level::playerLives = 3;
		Level::score = 0;
	}
    particleEngine.createParticleSet(formationType::radialOut, 300, 300, .5, 1.5);
}

Level::~Level() {
    projVec.clear();
    cometVec.clear();
    delete mainPlayer;
    delete iCollide;
    delete hud;
}

void Level::Draw() {    
	mainPlayer->Draw();
    particleEngine.drawParticleSet();
	hud->Thrust(mainPlayer->GetPosition().x(), mainPlayer->GetPosition().y()-25, mainPlayer->GetThrust(), 1);
	if (levelNum == 0 && !finishTutorial) {
		Tutorial();
	}
    /*if ((untilNext - kills) <= 10) {
        std::string remaining = itos(untilNext-kills)+" Remaining";
        hud->Status(remaining ,"FreeSans", mainPlayer->GetPosition().x()-40, 
            (*mainPlayer->GetPosition().y()-40, 13, 3);
    }*/    /*if (callCometScore) {
        int interval = 10;
        int timeout = SDL_GetTicks() + interval;
        cometScore = (rand() % 20);
        Level::score += cometScore;
        //std::string wtf2 = ("+" + itos(cometScore));
        hud->Status(wtf2.c_str(),"FreeSans", mainPlayer->GetPosition().x()-40, 
            mainPlayer->GetPosition().y()-40, 13, 3);
        callCometScore = false;
    }*/
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
    if (playerLives >= 0) {
        hud->Simple(Level::score, 12, 0, 10);
    } else {
        hud->Simple(Level::score, 72, (Window::Get_Surf()->w/2), (Window::Get_Surf()->h/2));
    }
    hud->Simple(untilNext-kills, 12, (Window::Get_Surf()->w/2), 10);
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
				if (mainPlayer->CanShoot()) {
					projVec.push_back(new Projectile(Projectile::PROJ_BASIC, iCollide,
					    mainPlayer->GetSpeed(), mainPlayer->GetPosition().x()+sinf(mainPlayer->GetAngle()), 
						mainPlayer->GetPosition().y()+cosf(mainPlayer->GetAngle()),
						mainPlayer->GetAngle()));
					mainPlayer->Shoot();
				}
				break;
		   }
		}
	}
	mainPlayer->Handle_Events();
}

void Level::Logic() {
    particleEngine.updateParticleSet();
    if (mainPlayer->GetAlive()) {
	mainPlayer->Logic();
        if (SDL_GetTicks() > cometSpawn) {
            cometVec.push_back(new Comet(iCollide, randOutside(0.0f, static_cast<float>(Window::Get_Surf()->w), 20.0f), 
                randOutside(0.0f,  static_cast<float>(Window::Get_Surf()->h), 20.0f), 
                static_cast<float>(rand() % 50+60), static_cast<float>(rand() % 50+60), (rand() % 3 + 5),  
                static_cast<float>((levelNum/10) + (Utility::UGen_Random(0.1, 1.0))), 
                mainPlayer->GetPosition()));
    		cometSpawn = SDL_GetTicks() + 2000;
        }
    } else {
        cometVec.clear();
        if (SDL_GetTicks() > playerRespawn) {
            if (playerLives > 0) {
        		playerLives--;
                delete mainPlayer;
                mainPlayer = new Player(iCollide, 320, 240, 25, 25);
        		playerRespawn = SDL_GetTicks() + 5000;
            } else {
                Set_State(StateManager::Child_Exit);
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
                ScoreIncrease();
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
    /*hud->Status(tutText.c_str() ,"FreeSans", (*mainPlayer->GetPosition().x()-40, 
        (*mainPlayer->GetPosition().y()-40, 13, 3);*/
    //finishTutorial = true;
}

/*void Level::CometScore() {
    hud->Status(itos(,"FreeSans", (*mainPlayer->GetPosition().x()-40, 
        (*mainPlayer->GetPosition().y()-40, 13, 3);
  */  

float Level::randOutside(float _first, float _second, float _distance) {
    int test = Utility::UGen_Random(_first, _second);
    if (test <= (_second-_first)/2) {
        return Utility::UGen_Random((_first-_distance), _first);
    } else {
        return Utility::UGen_Random((_second-_distance), _second);
    }
}

void Level::ScoreIncrease() {
    cometScore = (rand() % 20);
    Level::score += cometScore;
}

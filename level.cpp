#include "level.h"

int Level::playerLives = 3;
int Level::score = 0;

Level::Level(int _levelNum) : kills(0), callAnnouncement(true), announceSize(90), levelNum(_levelNum), stars(Starfield()), iCollide(new ICollide()), hud(new HUD(fe, true, true, true)), cometSpawn(SDL_GetTicks()+5000) { 
  mainPlayer = new Player(iCollide, 320, 240, 25, 25);
	untilNext = (levelNum + (rand() % 1 + 3))*(levelNum + (rand() % 1 + 3));
	if (levelNum == 1) {
		Level::playerLives = 3;
		Level::score = 0;
    untilNext = (levelNum + (rand() % 1 + 3))*(levelNum + (rand() % 1 + 3));
	}
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
	stars.Draw();
	if (!cometVec.empty()) {
        for (int i = 0; i < cometVec.size(); ++i) {
       		cometVec[i]->Draw();
        }
	}
	if (!projVec.empty()) {
        for (int i = 0; i < projVec.size(); ++i) {
        		projVec[i]->Draw();
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
					projVec.push_back(new Projectile(Projectile::PROJ_BASIC, iCollide, mainPlayer->GetSpeed(), mainPlayer->GetPosition().x()+sinf(mainPlayer->GetAngle()), mainPlayer->GetPosition().y()+cosf(mainPlayer->GetAngle()), mainPlayer->GetAngle()));
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
            cometVec.push_back(new Comet(iCollide, randOutside(0.0f, static_cast<float>(Window::Get_Surf()->w), 20.0f), randOutside(0.0f,  static_cast<float>(Window::Get_Surf()->h), 20.0f), static_cast<float>(rand() % 50+60), static_cast<float>(rand() % 50+60), (rand() % 3 + 5), static_cast<float>((levelNum/10) + (Utility::UGen_Random(0.1, 1.0))), mainPlayer->GetPosition()));
        		cometSpawn = SDL_GetTicks() + 2000;
        }
    } else {
        for (int i = 0; i < cometVec.size();) {
            delete cometVec[i];
            cometVec.erase(cometVec.begin() + i);
        }
        if (playerLives > 0) {
        		playerLives--;
            particleEngine.createParticleSet(formationType::radialOut, mainPlayer->GetPosition().x(), mainPlayer->GetPosition().y(), Utility::UGen_Random(0.1, 1.0), Utility::UGen_Random(0.5, 2.0));
            delete mainPlayer;
            mainPlayer = new Player(iCollide, 320, 240, 25, 25);
        } else {
            Set_State(StateManager::Child_Exit);
        }
    }
	if (!cometVec.empty()) {
        for (int i = 0; i < cometVec.size();) {
            if (cometVec[i]->GetAlive()) {
            		cometVec[i]->Logic();
                // Check bounds, set to wrap
                if ((cometVec[i]->GetPosition().x() > 0 && cometVec[i]->GetPosition().x() < Window::Get_Surf()->w) && (cometVec[i]->GetPosition().y() > 0 && cometVec[i]->GetPosition().y() < Window::Get_Surf()->h)) {
                        cometVec[i]->SetWrap(true);
                }
                ++i;
        		} else {                particleEngine.createParticleSet(formationType::radialOut, cometVec[i]->GetPosition().x(), 
                  cometVec[i]->GetPosition().y(), Utility::UGen_Random(0.1, 1.0), Utility::UGen_Random(0.5, 2.0));

                Vectorf test = cometVec[i]->GetPosition();
                numPoints = cometVec[i]->GetPoints();

                delete cometVec[i];
                cometVec.erase(cometVec.begin() + i);
                ++kills;
                ScoreIncrease();
                --numPoints;
                if (numPoints > 3) {
                  createCometChild(test, numPoints);
                }

                if (i != cometVec.size()) {
                    ++i;
                }
            }
        }
	}

	if (!projVec.empty()) {
        for (int i = 0; i < projVec.size();) {
            if (projVec[i]->GetAlive() && 
                !(projVec[i]->GetPosition().x() < -10 || projVec[i]->GetPosition().x() > Window::Get_Surf()->w+10 || projVec[i]->GetPosition().y() < -10 || projVec[i]->GetPosition().y() > Window::Get_Surf()->h+10)) {
        		projVec[i]->Logic();
                ++i;
			} else {
               delete projVec[i];
               projVec.erase(projVec.begin() + i);
                if (i != projVec.size()) {
                    ++i;
                }
            }
        }
    }
    // Switch Level
    if (kills == untilNext) {
        Set_State(StateManager::Child_Success);
    }
}

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

void Level::createCometChild(Vectorf _parentVec, int _n) {
  Vectorf randNew;
  int bleep = (rand() % 3);
    for (int i = 0; i < bleep; ++i) {
      randNew.set(Utility::UGen_Random(0.1, 360.0), Utility::UGen_Random(0.1, 360.0), 0);
        cometVec.push_back(new Comet(iCollide, _parentVec.x(), _parentVec.y(), 
            static_cast<float>(rand() % 20+30), static_cast<float>(rand() % 20+30), numPoints,  
            static_cast<float>((levelNum/10) + (Utility::UGen_Random(0.1, 1.0))), 
            randNew));
    }
}

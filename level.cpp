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
  hud->Lives(Window::Get_Surf()->w-50, 10, playerLives);
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
      hud->Announcement(itos(levelNum).c_str(), "04b_11", Window::Get_Surf()->w/2, Window::Get_Surf()->h/2, announceSize);
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
          cometVec.push_back(new Comet(iCollide, randOutside(Window::Get_Surf()->w, Window::Get_Surf()->h, 0, 75), static_cast<float>(rand() % 40+50), static_cast<float>(rand() % 40+50), (rand() % 3 + 6), static_cast<float>((levelNum/10) + (Utility::UGen_Random(0.1, 1.0))), mainPlayer->GetPosition()));
        		cometSpawn = SDL_GetTicks() + 2000;
        }
    } else {
      // Still ugly code...... meh
     for (int i = (cometVec.size()-1); i >= 0; --i) {
       delete cometVec[i];
       cometVec.erase(cometVec.begin() + i);
     }
        if (playerLives > 0) {
        		playerLives--;
            particleEngine.createParticleSet(formationType::radialOut, mainPlayer->GetPosition().x(), mainPlayer->GetPosition().y(), Utility::UGen_Random(0.1, 0.8), Utility::UGen_Random(0.5, 2.0));
            delete mainPlayer;
            mainPlayer = new Player(iCollide, 320, 240, 25, 25);
        } else {
            Set_State(StateManager::Child_Exit);
        }
    }

	if (!cometVec.empty()) {
        for (int i = 0; i < cometVec.size(); ++i) {
            if (cometVec[i]->GetAlive()) {
            		cometVec[i]->Logic();
                // Check bounds, set to wrap
                if ((cometVec[i]->GetPosition().x() > 0 && cometVec[i]->GetPosition().x() < Window::Get_Surf()->w) && (cometVec[i]->GetPosition().y() > 0 && cometVec[i]->GetPosition().y() < Window::Get_Surf()->h)) {
                        cometVec[i]->SetWrap(true);
                }
        		} else {                particleEngine.createParticleSet(formationType::radialOut, cometVec[i]->GetPosition().x(), cometVec[i]->GetPosition().y(), Utility::UGen_Random(0.3, 1.0), Utility::UGen_Random(0.5, 2.0));

                numPoints = cometVec[i]->GetPoints()-1;

                if (numPoints > 3) {
                  createCometChild(cometVec[i]->GetPosition(), numPoints);
                }

                delete cometVec[i];
                cometVec.erase(cometVec.begin() + i);
                ++kills;
                ScoreIncrease();
            }
        }
	}

	if (!projVec.empty()) {
        for (int i = 0; i < projVec.size(); ++i) {
            if (projVec[i]->GetAlive() && !(projVec[i]->GetPosition().x() < -10 || projVec[i]->GetPosition().x() > Window::Get_Surf()->w+10 || projVec[i]->GetPosition().y() < -10 || projVec[i]->GetPosition().y() > Window::Get_Surf()->h+10)) {
              projVec[i]->Logic();
        		} else {
              delete projVec[i];
              projVec.erase(projVec.begin() + i);
            }
        }
    }
    // Switch Level
    if (kills == untilNext) {
        Set_State(StateManager::Child_Success);
    }
}

Vectorf Level::randOutside(float _xMax, float _yMax, float _min, float _dist) {
  Vectorf tempPos;
  int side = (rand() % 3);
  switch (side) {
  case 0: // Top
    tempPos.x() = Utility::UGen_Random(_min, _xMax);
    tempPos.y() = _min-_dist;
    break;
  case 1: // Right
    tempPos.x() = _xMax+_dist;
    tempPos.y() = Utility::UGen_Random(_min, _yMax);
    break;
  case 2: // Bottom
    tempPos.x() = Utility::UGen_Random(_min, _xMax);
    tempPos.y() = _yMax+_dist;
    break;
  case 3: // Left
    tempPos.x() = Utility::UGen_Random(_min-_dist, _min);
    tempPos.y() = _yMax+_dist;
    break;
  }

  return tempPos;
}

void Level::ScoreIncrease() {
    cometScore = (rand() % 20);
    Level::score += cometScore;
}

void Level::createCometChild(Vectorf& _parentVec, int _n) {
  int amount = (rand() % 3);
  if (amount > 0) {
    Vectorf randNew;
    for (int i = 0; i < amount; ++i) {
      randNew.set(rand() % 359, rand() % 359, 0);
      cometVec.push_back(new Comet(iCollide, _parentVec, static_cast<float>(rand() % 20+30), static_cast<float>(rand() % 20+30), _n, static_cast<float>((levelNum/10) + (Utility::UGen_Random(0.1, 1.0))), randNew));
    }
  }
}

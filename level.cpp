#include "level.h"

int Level::lineOffset = 0;

Level::Level(int levelNum) {
	f_HUD = TTF_OpenFont("FreeSans.ttf", 48);
	totalAlive = 0;
	r_Formation.x = 150;
	r_Formation.y = 50;
	//player = new Player();
	//comet = new Comet();
	curr_x = r_Formation.x, curr_y = r_Formation.y;
    //Level::lineOffset = levelNum*111;
	Load_Level();
}

Level::~Level() {
	enemyVec.clear();
    SDL_FreeSurface(s_Score);
	SDL_FreeSurface(s_Lives);
}

bool Level::Load_Level() {
/*
	fl_currLevel.open ("data/levels.ob");
	fl_currLevel.seekg(Level::lineOffset, std::ios::beg);
	std::getline(fl_currLevel, line);
    ss << line;
	int j = 0;
	for (unsigned int i = 0; i < line.length(); i++) {
		if (ispunct(line[i])) {
			continue;
		}
		blockVec.push_back(new Block(curr_x, curr_y, line[i]-'0'));
		if (line[i] != 0)
			totalAlive++;

		if (j >= ROWS-1) {
			j = 0;
			curr_x = r_Formation.x;
        	curr_y += blockVec[blockVec.size()-1]->Get_Rect().h;
		} else {
			j++;
            curr_x += blockVec[blockVec.size()-1]->Get_Rect().w;
		}
	}
	return true;
	*/
	return true;
}

void Level::Draw() {
	SDL_FillRect(Window::Get_Surf(), NULL, SDL_MapRGB(Window::Get_Surf()->format, 0, 0, 0));
	for (int i=0; i < COLUMNS; i++) {
        for (int j = 0; j < ROWS; j++) {
            enemyVec[(i*ROWS+j)]->Draw();
        } 
    }

	Surface::Apply_Surface(30, Window::Get_Surf()->h-s_Score->h, s_Score);
	Surface::Apply_Surface(Window::Get_Surf()->w-30, Window::Get_Surf()->h-s_Score->h, s_Lives);
    player->Draw();
/*	if (isStart) {
		SDL_Delay(1000);
		isStart = false;
	}*/
}

void Level::Handle_Events() {
	while(SDL_PollEvent(Event::Get_Event())) {
		if (Event::Get_Event()->type == SDL_QUIT) {
			Set_State(StateManager::Child_Quit);
		} else if (Event::Get_Event()->type == SDL_KEYDOWN) {
			switch (Event::Get_Event()->key.keysym.sym) {
                    case SDLK_ESCAPE: 
						Set_State(StateManager::Child_Exit);
						Level::lineOffset = 0;
						Player::numLives = 3;
            			//global::score = 0;
                        break;
					case SDLK_n:
						Set_State(StateManager::Child_Success);
						break;
               }
		}
    	player->Handle_Events();
	}    	
	for (int i=0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
        	enemyVec[(i*ROWS+j)]->Handle_Events();
    	} 
	}
}

void Level::Logic() {

    //s_Score = TTF_RenderText_Blended(f_HUD, itos(global::score).c_str(), global::col_Gray);
	//s_Lives = TTF_RenderText_Blended(f_HUD, itos(Player::numLives).c_str(), global::col_Gray);

	player->Logic();
	/*
	if ((ball->Get_Rect().y+ball->Get_Rect().h) > Window::Get_Surf()->h) {
    	player->Set_Lives(-1);
		if (player->Get_Lives() <= 0) {
            Level::lineOffset = 0;
			global::score = 0;
    		Player::numLives = 3;
			Set_State(state::CHILD_EXIT);
		} else {
    		delete ball;
    		ball = new Ball();
			SDL_Delay(500);
		}
	} else if ((ball->Get_Rect().y+ball->Get_Rect().h) > 400) {
		if (ball->isCollision(*player) == true) {
			ball->Eval_Deflect(*player);
		}
	} else if (ball->Get_Rect().y < 200) {
    	for (int i=0; i < COLUMNS; i++) {
    		for (int j = 0; j < ROWS; j++) {
    			if (blockVec[(i*ROWS+j)]->GetAlive() != false) {
					if (ball->isCollision(*blockVec[(i*ROWS+j)]) == true) {
						ball->Eval_Deflect(*blockVec[(i*ROWS+j)]);
						if (blockVec[(i*ROWS+j)]->isPopped() == true) {
    						totalAlive--;
						}
					}
				}
    			if (totalAlive <= 0) {
					Set_State(state::CHILD_SUCCESS);	
				}
    		} 
		}
	}
	*/
}
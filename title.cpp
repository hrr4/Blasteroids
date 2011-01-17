#include "title.h"

Title::Title() {
	iCollide = new ICollide();
	player = new Player(iCollide, 400, 301, 25, 25);
	starfield = new Starfield();
	projVec.reserve(5);
	cometVec.reserve(5);
	//face = new OGLFT::Monochrome("04b_14.ttf", 14);

	/*
    SDL_Color col_Grey = {175, 175, 175};
    SDL_Color col_White = {255, 255, 255};
	f_Title = TTF_OpenFont("04b_11.ttf", 12);
	f_Banner = TTF_OpenFont("04b_11.ttf", 48);
	s_NewButton = TTF_RenderText_Blended(f_Title, "New Game", col_Grey);
	s_HScore = TTF_RenderText_Blended(f_Title, "High Scores", col_Grey);
	s_Options = TTF_RenderText_Blended(f_Title, "Options", col_Grey);
	s_QuitButton = TTF_RenderText_Blended(f_Title, "Exit", col_Grey);
	s_Selector = TTF_RenderText_Blended(f_Title, ">                   <", col_White);
	s_Title = TTF_RenderText_Blended(f_Banner, "Comets!", col_White);

	r_Title.x = ((s_NewButton->w)/2 + ((Window::Get_Surf()->w)/3)/2);
	r_Title.y = 20;
	r_NewButton.x = ((s_NewButton->w)/2 + ((Window::Get_Surf()->w)/3));
	r_NewButton.y = 300;

	r_HScore.x = r_NewButton.x-15;
	r_HScore.y = r_NewButton.y+30;

	r_Options.x = r_NewButton.x+10;
	r_Options.y = r_NewButton.y+60;

	r_QuitButton.x = r_NewButton.x+30;
	r_QuitButton.y = r_NewButton.y+90;

	r_Selector.x = r_NewButton.x-30;
	r_Selector.y = r_NewButton.y;
	*/
}

Title::~Title() {
/*
	TTF_CloseFont(f_Title);
	SDL_FreeSurface(s_Selector);
	SDL_FreeSurface(s_NewButton);
	SDL_FreeSurface(s_HScore);
	SDL_FreeSurface(s_Options);
	SDL_FreeSurface(s_QuitButton);
	SDL_FreeSurface(s_Title);
	*/
	while(!projVec.empty()) {
		projVec.back();
		projVec.pop_back();
	}
	//delete &projVec;
}

void Title::Draw() {
/*
	Window::Fill(0, 0, 0);
	Surface::Apply_Surface(r_NewButton.x, r_NewButton.y, s_NewButton, Window::Get_Surf());
	Surface::Apply_Surface(r_HScore.x, r_HScore.y, s_HScore, Window::Get_Surf());
	Surface::Apply_Surface(r_Options.x, r_Options.y, s_Options, Window::Get_Surf());
	Surface::Apply_Surface(r_QuitButton.x, r_QuitButton.y, s_QuitButton, Window::Get_Surf());
	Surface::Apply_Surface(r_Selector.x, r_Selector.y, s_Selector, Window::Get_Surf());
	Surface::Apply_Surface(r_Title.x, r_Title.y, s_Title, Window::Get_Surf());
	*/
	player->Draw();
	starfield->Draw();
	if (!cometVec.empty()) {
    	for (unsigned int i=0; i<cometVec.size(); ++i)
    		cometVec[i]->Draw();
	}
	if (!projVec.empty()) {
    	for (unsigned int i=0; i<projVec.size(); ++i)
    		projVec[i]->Draw();
	}
	//face->draw(20, 20, "LOL TEST");
}

void Title::Handle_Events() {
	//int x, y = 0;
	while(SDL_PollEvent(Event::Get_Event())) {
		if (Event::Get_Event()->type == SDL_QUIT) {
			Set_State(StateManager::Child_Quit);
		} /*else if (Event::Get_Event()->type == SDL_MOUSEBUTTONDOWN) {
           if (Event::Get_Event()->button.button == SDL_BUTTON_LEFT) {
			   x = Event::Get_Event()->button.x;
    			y = Event::Get_Event()->button.y;

			if ((x > r_NewButton.x) && (x < (r_NewButton.x+r_NewButton.w)) && (y > r_NewButton.y) && (y < (r_NewButton.y+r_NewButton.h))) {
				Set_State(StateManager::Child_Success);
    		} else if ((x > r_QuitButton.x) && (x < (r_QuitButton.x+r_QuitButton.w)) && (y > r_QuitButton.y) && (y < (r_QuitButton.y+r_QuitButton.h))) {
				Set_State(StateManager::Child_Quit);
			}
		   }
		}*/ else if (Event::Get_Event()->type == SDL_KEYDOWN) {
			switch (Event::Get_Event()->key.keysym.sym) {
                case SDLK_ESCAPE : 
						Set_State(StateManager::Child_Quit);
                        break;
					case SDLK_UP :
						if (r_Selector.y > r_NewButton.y) {
							r_Selector.y -= 30;
						} 
						break;
					case SDLK_DOWN :
						if (r_Selector.y < r_NewButton.y+90) {
							r_Selector.y += 30;
						}
						break;
					case SDLK_RETURN :
						// New Game
						if (r_Selector.y == r_NewButton.y) {
							Set_State(StateManager::Child_Success);
						} else if (r_Selector.y == r_NewButton.y+30) {
							// Write a High Score Function?
						} else if (r_Selector.y == r_NewButton.y+60) {
							// Write an Options Function?
						} else if (r_Selector.y == r_NewButton.y+90) {
							Set_State(StateManager::Child_Quit);
						}
						break;
					case SDLK_SPACE:
						if (player->CanShoot()) {
							projVec.push_back(new Projectile(Projectile::PROJ_BASIC, iCollide,
								player->GetPosition().x()+sinf(player->GetAngle()), 
								player->GetPosition().y()+cosf(player->GetAngle()),
								player->GetAngle()));
							player->Shoot();
						}
            			break;
					case SDLK_c:
						cometVec.push_back(new Comet(iCollide, 300, 300, (rand() % 50+60), (rand() % 50+60), 
							(rand() % 3 + 5), 5, player->GetPosition()));
            			break;
           }
		}
	}
	player->Handle_Events();
}

void Title::Logic() {
	//std::vector<Collider*>::iterator it;
	starfield->Logic();
	if (player->GetAlive()) {
    	player->Logic();
	} else {
		delete player;
	}
	if (!projVec.empty()) {
    	for (unsigned int i=0; i<projVec.size(); ++i)
			if (projVec[i]->GetAlive()) {
        		projVec[i]->Logic();
			} else {
				delete projVec[i];
				//projVec.pop_back();
			}
	}
	if (!cometVec.empty()) {
    	for (unsigned int i=0; i<cometVec.size(); ++i) {
        	if (!cometVec[i]->CheckCollision()) {
        		cometVec[i]->Logic();
        	} else {
				delete cometVec[i];
				//cometVec.pop_back();
			}
		}
	}
}

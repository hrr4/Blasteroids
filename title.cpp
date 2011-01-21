#include "title.h"

Title::Title() : selectorX(230), selectorY(200) {
    fe = new FontEngine("04b_11.ttf");    fe->AddFont("FreeSans.ttf");
    starfield = new Starfield();

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
}

void Title::DrawMenu() {
glPushMatrix();    glColor4f(1,1,1,1);
    //glScalef(1, -1, 1);

    //TEST = fe->Draw("Blasteroids", 48, "04b_11", 50, 400);
    fe->Draw("New Game", 12, "04b_11", 250, 200);
    fe->Draw("High Scores", 12, "04b_11", 250, 180);
    fe->Draw("Options", 12, "04b_11", 250, 160);
    fe->Draw("Quit Game", 12, "04b_11", 250, 140);
    fe->Draw(">                    <", 12, "04b_11", selectorX, selectorY);
glPopMatrix();
}

void Title::Draw() {
    starfield->Draw();
    DrawMenu();
}

void Title::Handle_Events() {
	while(SDL_PollEvent(Event::Get_Event())) {
		if (Event::Get_Event()->type == SDL_QUIT) {
			Set_State(StateManager::Child_Quit);
		} else if (Event::Get_Event()->type == SDL_KEYDOWN) {
			switch (Event::Get_Event()->key.keysym.sym) {
                case SDLK_ESCAPE : 
						Set_State(StateManager::Child_Quit);
                        break;
            	case SDLK_UP :
            		if (selectorY > 200) {
            			selectorY -= 30;
            		}
            		break;
            	case SDLK_DOWN :
            		if (selectorY > 200) {
            			selectorY += 30;
            		}
            		break;
            	case SDLK_RETURN :
            		// New Game
            		if (selectorY == r_NewButton.y) {
            			Set_State(StateManager::Child_Success);
            		} else if (r_Selector.y == r_NewButton.y+30) {
            			// Write a High Score Function?
            		} else if (r_Selector.y == r_NewButton.y+60) {
            			// Write an Options Function?
            		} else if (r_Selector.y == r_NewButton.y+90) {
            			Set_State(StateManager::Child_Quit);
            		}
            		break;
           }
		}
	}
}

void Title::Logic() {
	starfield->Logic();
}

#include "title.h"

Title::Title() : selectorX(Window::Get_Surf()->w-105), selectorY(Window::Get_Surf()->h-45) {
    stars = Starfield();
    active = Main;
}

Title::Title(Screen forceScreen) : selectorX(Window::Get_Surf()->w-105), selectorY(Window::Get_Surf()->h-45) {
    stars = Starfield();
    active = forceScreen;
}

Title::~Title() {}

void Title::DrawMain() {
    //TEST = fe->Draw("Blasteroids", 48, "04b_11", 50, 400);
    glColor4f(1,1,1,.8);
    fe->Draw("Blasteroids", 52, "04b_11", 30, 80);
    glColor4f(1,1,1,.5);
    fe->Draw("Engage!", 12, "04b_11", Window::Get_Surf()->w-90, Window::Get_Surf()->h-45);
    fe->Draw("Scores", 12, "04b_11", Window::Get_Surf()->w-85, Window::Get_Surf()->h-30);
    fe->Draw("Options", 12, "04b_11", Window::Get_Surf()->w-90, Window::Get_Surf()->h-15);
    fe->Draw("Quit", 12, "04b_11", Window::Get_Surf()->w-45, Window::Get_Surf()->h);
    glColor4f(1,1,1,.9);
    fe->Draw(">", 12, "04b_11", selectorX, selectorY);
}

void Title::DrawScores() {
    glColor4f(1,1,1,.8);
    fe->Draw("Blasteroids", 52, "04b_11", 30, 80);
    glColor4f(1,1,1,.5);
   /* fe->Draw("Engage!", 12, "04b_11", Window::Get_Surf()->w-90, -(Window::Get_Surf()->h-45));
    fe->Draw("Scores", 12, "04b_11", Window::Get_Surf()->w-85, -(Window::Get_Surf()->h-30));
    fe->Draw("Options", 12, "04b_11", Window::Get_Surf()->w-90, -(Window::Get_Surf()->h-15));
    fe->Draw("Back", 12, "04b_11", Window::Get_Surf()->w-45, -(Window::Get_Surf()->h));*/
    glColor4f(1,1,1,.9);
    fe->Draw(">", 12, "04b_11", selectorX, selectorY);
}

void Title::DrawOptions() {
    glColor4f(1,1,1,.8);
    fe->Draw("Blasteroids", 52, "04b_11", 30, -80);
    glColor4f(1,1,1,.5);
    fe->Draw("Fullscreen / Windowed", 12, "04b_11", Window::Get_Surf()->w-265, Window::Get_Surf()->h-45);
    /*fe->Draw("Scores", 12, "04b_11", Window::Get_Surf()->w-85, -(Window::Get_Surf()->h-30));
    fe->Draw("Options", 12, "04b_11", Window::Get_Surf()->w-90, -(Window::Get_Surf()->h-15));*/
    fe->Draw("Back", 12, "04b_11", Window::Get_Surf()->w-45, Window::Get_Surf()->h);
    glColor4f(1,1,1,.9);
    fe->Draw(">", 12, "04b_11", selectorX, selectorY);
}
void Title::Draw() {
    stars.Draw();
    switch (active) {
        case Main:
            DrawMain();
            break;
        case Scores:
            DrawScores();
            break;
        case Options:
            DrawOptions();
            break;
    }
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
            		if (selectorY > Window::Get_Surf()->h-45) {
            			selectorY -= 15;
            		}
            		break;
            	case SDLK_DOWN :
            		if (selectorY < Window::Get_Surf()->h) {
            			selectorY += 15;
            		}
            		break;
            	case SDLK_RETURN :
            		if (selectorY == Window::Get_Surf()->h-45) {
            			Set_State(StateManager::Child_Success);
            		} else if (selectorY == Window::Get_Surf()->h-30) {
                        active = Scores;
            		} else if (selectorY == Window::Get_Surf()->h-15) {
                        active = Options;
            		} else if (selectorY == Window::Get_Surf()->h) {
            			Set_State(StateManager::Child_Quit);
            		}
            		break;
           }
		}
	}
}

void Title::Logic() {}

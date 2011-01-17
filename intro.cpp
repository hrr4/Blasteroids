#include "intro.h"

Intro::Intro() {
	s_Background = Surface::Load_Image("logo.png");
}

Intro::~Intro() {}

void Intro::Draw() {
	Surface::Apply_Surface(0, 0, s_Background, Window::Get_Surf());
}

void Intro::Handle_Events() {
	while(SDL_PollEvent(Event::Get_Event())) {
		if (Event::Get_Event()->type == SDL_QUIT) {
			Set_State(StateManager::Child_Quit);
		} else if (Event::Get_Event()->type == SDL_MOUSEBUTTONDOWN) {
           if (Event::Get_Event()->button.button == SDL_BUTTON_LEFT)
			   Set_State(StateManager::Child_Success);
		} else if (Event::Get_Event()->type == SDL_KEYDOWN) {
			switch (Event::Get_Event()->key.keysym.sym) {
			case SDLK_ESCAPE :
				Set_State(StateManager::Child_Quit);
				break;
			}
		}
	} 
}

void Intro::Logic() {}
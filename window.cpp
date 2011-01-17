#include "window.h"

SDL_Surface* Window::s_Screen = NULL;

Window::Window(const int w, const int h, const int bpp, const int flags) {
	s_Screen = SDL_SetVideoMode(w, h, bpp, flags);
	SDL_WM_SetCaption("Comets!",NULL);
	Grab = SDL_WM_GrabInput(SDL_GRAB_OFF);
	cursorVis = SDL_ShowCursor(SDL_ENABLE);
}	

Window::~Window() {}

void Window::Fill(const int r=255, const int g=255, const int b=255) {
	SDL_FillRect(s_Screen, NULL, SDL_MapRGB(s_Screen->format, r, g, b));
}

SDL_Surface* Window::Get_Surf() {
	return s_Screen;
}

int Window::Get_Vis() const {
	return cursorVis;
}
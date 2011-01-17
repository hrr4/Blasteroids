#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window {
public:
	Window(const int w, const int h, const int bpp, const int flags=SDL_HWSURFACE);
	~Window();
	static SDL_Surface* Get_Surf();
	int Get_Vis() const;
	static void Fill(const int r, const int g, const int b);
private:
	static SDL_Surface* s_Screen;
	SDL_GrabMode Grab;
	int cursorVis;
};
#endif
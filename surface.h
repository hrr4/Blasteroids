#ifndef SURFACE_H
#define SURFACE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "window.h"

struct Surface {
	static bool Apply_Surface(int x, int y, SDL_Surface* src, SDL_Surface* dst=Window::Get_Surf(), SDL_Rect* clip=NULL);
    static SDL_Surface* Load_Image(std::string filename, bool key=false);
};

#endif
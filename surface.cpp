#include "surface.h"

bool Surface::Apply_Surface(int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect* clip) {
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	if (SDL_BlitSurface(src, clip, dst, &offset))
		return true;
	return false;
}

SDL_Surface* Surface::Load_Image(std::string filename, bool key) {
    filename = "data/" + filename;

    SDL_Surface* loadedImage = IMG_Load(filename.c_str());
    SDL_Surface* optimizedImage = SDL_DisplayFormat(loadedImage);

    SDL_FreeSurface(loadedImage);

    if (key == true)
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, 
            SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF));

    return optimizedImage;
}
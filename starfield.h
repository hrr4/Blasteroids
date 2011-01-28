#ifndef STARFIELD_H
#define STARFIELD_H

#include <SDL_opengl.h>
#include <vector>
#include "star.h"

struct Starfield {
	Starfield();
	~Starfield();
	virtual void Draw();
private:
    std::vector<Star> starVec;
};
#endif
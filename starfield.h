#ifndef STARFIELD_H
#define STARFIELD_H

#include "Entity.h"
#include "fps.h"
#include <SDL_opengl.h>
#include <vector>
#include "Utility.h"
#include "star.h"

//class Starfield : public Entity {
struct Starfield {
	Starfield();
	~Starfield();
	virtual void Draw();
private:
    std::vector<Star> starVec;
};
#endif
#ifndef STARFIELD_H
#define STARFIELD_H

#include "Entity.h"
#include "fps.h"
#include <SDL_opengl.h>
#include <vector>
#include "Utility.h"
#include "star.h"

class Starfield : public Entity {
public:
	Starfield();
	virtual ~Starfield();
	virtual void Draw();
	virtual void Logic();
	virtual void Handle_Events();
private:
    void Render();
	int speed, r, g, b, points;
    std::vector<Star> starVec(5);
};
#endif
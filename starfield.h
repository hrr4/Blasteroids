#ifndef STARFIELD_H
#define STARFIELD_H

#include "entity.h"
#include "fps.h"
#include <SDL_opengl.h>
#include <vector>
#include "Utility.h"

class Starfield : public Entity {
public:
	Starfield();
	virtual ~Starfield();
	virtual void Draw();
	virtual void Logic();
	virtual void Handle_Events();
private:
	void RandomizePoints(Sint16& x, Sint16& y, Uint16& w, Uint16& h, int n);
    void Render();
    float a;
	int speed, r, g, b, points;
	std::vector<float> vertVec;
};
#endif
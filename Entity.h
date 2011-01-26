#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "window.h"
#include "surface.h"
#include "event.h"
#include "fps.h"
#include "vector.h"
#include <list>
#include <SDL_opengl.h>

class Entity {
public:
	virtual ~Entity();
	virtual void Handle_Events()=0;
	virtual void Logic()=0;
	virtual void Draw()=0;
	virtual Vectorf GetPosition() const;
	bool GetAlive() const;
	float GetRadius() const;
	float GetAngle() const;
	int GetLayer() const;
protected:
	SDL_Rect r_Rect, r_Clip;
	float angle, speed, radius, a; 
	bool isAlive, isPassable;
	Vectorf Position, Velocity, Acceleration, Direction;
	int layer;
};

#endif
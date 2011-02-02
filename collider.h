#ifndef COLLIDER_H
#define COLLIDER_H

#include "Entity.h"
#include "observer.h"
#include "icollide.h"

class Collider : public Observer, public Entity {
public:
    Collider();
	virtual ~Collider();
	bool CheckCollision();
protected:
	//Collider();
	ICollide* _collide;
};

#endif
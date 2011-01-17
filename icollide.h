#ifndef ICOLLIDE_H
#define ICOLLIDE_H

#include "Entity.h"
#include "observer.h"
#include "subject.h"
#include <list>

class Collider;

// CLASS ICOLLIDE
class ICollide : public Subject {
public:
	virtual ~ICollide();
	Collider* FindNearest(Collider*);
	bool TestRadii(Collider*, Collider*);
	bool TestAABB(Collider*);
};

#endif
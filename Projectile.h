#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Utility.h"
#include "icollide.h"
#include "collider.h"
#include <vector>
#include <math.h>

class Projectile : public Collider {
public:
	enum Projectile_Type {PROJ_BASIC, PROJ_SPREAD, PROJ_SIDEF, PROJ_BACKF};
public:
	Projectile(Projectile_Type projType, ICollide* c, Vectorf _v, float _x, float _y, float _angle, float _r=1, float _g=1, float _b=1, float _a=1);
	virtual ~Projectile();
	virtual void Logic();
	virtual void Handle_Events();
	virtual void Draw();
    virtual void Update(Subject*);
private:
	void Render(float r, float g, float b, float a);
	float r, g, b, a, heading;
	static float projVec[12];
	int fadetimeout, offset;
};

#endif
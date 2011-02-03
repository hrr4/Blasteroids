#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "collider.h"
#include "Utility.h"
#include <vector>
#include <math.h>

class Player : public Collider {
public:
    Player();
	Player(ICollide* c, int _x, int _y, int w, int h);
	virtual ~Player();
	virtual void Draw();
	virtual void Logic();
	virtual void Handle_Events();
	bool CanShoot() const;
	static int numLives;
	virtual void Update(Subject*);
	void Shoot();
    float GetThrust() const;
    Vectorf GetSpeed() const;
private:
	void Render();
	float a, thrust, Heading, Rotation, Force; 
	bool up_pressed, canShoot, burnout;
	static float vertArray[9]; 
	int centerx, centery, length, winheight, winwidth, mass, shootTimeout, ticksOffset; 
};
#endif
#include "Projectile.h"

float Projectile::projVec[12] = {-2, 2, 0, -2, -2, 0, 2, -2, 0, 2, 2, 0};

Projectile::Projectile(Projectile_Type projType, ICollide* c, Vectorf _v, float _x, float _y, float _angle, 
	float _r, float _g, float _b, float _a) :
	offset(100) {
	Position.x() = _x, Position.y() = _y, angle = _angle, r = _r, g = _g, b = _b, a = _a;
	Position.z() = 0;
	radius = 10;
	speed = 5;
	layer = 1;

	angle *= Utility::DEGTORAD;
	fadetimeout = SDL_GetTicks()+offset;
	isAlive = true;
	isPassable = false;

    Velocity.x() = speed * sinf(angle) + _v.x();
	Velocity.y() = speed * cosf(angle) + _v.y();

	speed = sqrtf(Velocity.x()*Velocity.x() + Velocity.y()*Velocity.y());

	if (Velocity.y() >= 0)
		heading = atanf(Velocity.x()/Velocity.y());
	else 
		heading = atanf(Velocity.x()/Velocity.y())+Utility::PI;

	angle *= Utility::RADTODEG;
	_collide = c;
	_collide->Attach(this);
}

Projectile::~Projectile() {
	_collide->Detach(this);
}

void Projectile::Draw() {
	if (isAlive)
		Render(r, g, b, a);
}

void Projectile::Render(float r, float g, float b, float a) {
glPushMatrix();
	glTranslatef(Position.x(), Position.y(), Position.z());
	glRotatef(angle, 0, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, projVec);
    glColor4f(r, g, b, a);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glFlush();
glPopMatrix();
}

void Projectile::Logic() {
	 Position.x() += speed * sinf(heading);
	 Position.y() -= speed * cosf(heading);
	 if (fadetimeout < SDL_GetTicks() && a > 0) {
		 a -= 0.15;
		 fadetimeout = SDL_GetTicks()+offset;
	 }
	 if (a <= 0 || CheckCollision()) 
		isAlive = false;
}

void Projectile::Update(Subject* ChangedSubject) {
	if (ChangedSubject != _collide) {
		_collide = static_cast<ICollide*>(ChangedSubject);
	}
}

void Projectile::Handle_Events() {}
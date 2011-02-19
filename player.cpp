#include "player.h"

int Player::numLives = 3;

float Player::vertArray[9] = {-10, 10, 0, 10, 10, 0, 0, -20, 0};

Player::Player() {}

Player::Player(ICollide* c, int _x, int _y, int w, int h) :
    up_pressed(false), burnout(false), canShoot(true), a(1), ticksOffset(400), mass(50) {
	isPassable = false, isAlive = true;
	Position.x() = _x, Position.y() = _y, r_Rect.w = w, r_Rect.h = h;
	radius = 10;
	layer = 1;

	shootTimeout = SDL_GetTicks()+ticksOffset;

	centerx = r_Rect.w/2+Position.x();
	centery = r_Rect.h/2+Position.y();
	winwidth = Window::Get_Surf()->w;
	winheight = Window::Get_Surf()->h;

	mass = 50;

	thrust = Force = Position.z() = 0;
	Velocity.x() = Velocity.y() = angle = 0.1;
	Heading = 0.5;
	Rotation = 3;
	speed = 0.2;
	_collide = c;
	_collide->Attach(this);
}

Player::~Player() {
	glDisableClientState(GL_VERTEX_ARRAY);
	_collide->Detach(this);
}

void Player::Draw() {
	if (isAlive == true)
		Render();
}

void Player::Render() {
glPushMatrix();
	glTranslatef(Position.x(), Position.y(), Position.z());
	glRotatef(angle, 0, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertArray);
    glColor4f(1, 1, 1, 1);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glFlush();
glPopMatrix();
}

void Player::Logic() {
    angle *= Utility::DEGTORAD;
    Force = thrust/mass;

    if (up_pressed && !burnout) {
        if (thrust < 4) {
        		/*Acceleration.x() += 0.05;
        		Acceleration.y() += 0.05;*/
            thrust += 0.05;
        } else { burnout = true; }

        Velocity.x() += sinf(angle)*Force;
        Velocity.y() += cosf(angle)*Force;
            
        Position.x() += Velocity.x();
    		Position.y() -= Velocity.y();
    
    		angle *= Utility::RADTODEG;

    } else {
    		if (thrust > 0) {
        		thrust *= .5;
        		/*Acceleration.x() *= 0.05;
        		Acceleration.y() *= 0.05;*/
    		}
    		if (thrust <= 0)
    			burnout = false;
            
    		Velocity.x() -= sinf(angle)*Force;
        Velocity.y() -= cosf(angle)*Force;
    
        Position.x() += Velocity.x();
    		Position.y() -= Velocity.y();
    
    		angle *= Utility::RADTODEG;
	}

	if (Position.x() < 0) {
		Position.x() = winwidth;
	} else if (Position.y() < 0) {
		Position.y() = winheight;
	} else if (Position.x() > winwidth) {
		Position.x() = 0;
	} else if (Position.y() > winheight) {
		Position.y() = 0;
	}

	if (CheckCollision()) { isAlive = false; }
	
	if (shootTimeout < SDL_GetTicks()) {
		canShoot = true;
		shootTimeout = SDL_GetTicks()+ticksOffset;
	}
}

void Player::Shoot() {
    if(canShoot) 
        canShoot = false;
}

void Player::Handle_Events() {
	if (Event::Get_Event()->type == SDL_KEYDOWN) {
    switch (Event::Get_Event()->key.keysym.sym) {
        case SDLK_LEFT: angle -= Rotation; break;
        case SDLK_RIGHT: angle += Rotation; break;
        case SDLK_UP: up_pressed = true; break;
		}
  } else if (Event::Get_Event()->type == SDL_KEYUP) {
        switch (Event::Get_Event()->key.keysym.sym) {
            case SDLK_UP: up_pressed = false; break;
        }
	}
}

void Player::Update(Subject* ChangedSubject) {
	if (ChangedSubject != _collide) {
		_collide = static_cast<ICollide*>(ChangedSubject);
	}
}
bool Player::CanShoot() const {return canShoot;}

float Player::GetThrust() const { return thrust; }

Vectorf Player::GetSpeed() const { return Velocity; }
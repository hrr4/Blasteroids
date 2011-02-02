#include "comet.h"

Comet::Comet(ICollide* c, float _x, float _y, float _w, float _h, int _n, float _vel, Vectorf _vec, int _r, int _g, int _b, int _a) :
        inBounds(false) {
	Position.x() = _x, Position.y() = _y, r_Rect.w = _w, r_Rect.h = _h;
	r = _r, g = _g, b = _b, a = _a, n = _n;
	Position.z() = angle = 0;
    	speed = _vel;
	radius = (_h/2) + ((_w*_w)/(8*_h));
    	centerx = Position.x()+r_Rect.w/2;
	centery = Position.y()+r_Rect.h/2;

	layer = 2;
	// Vector Subtraction gives us the vectors we need to shoot the comet at the player just once though
	Direction.x() = Position.x() - _vec.x();
	Direction.y() = Position.y() - _vec.y();
	Direction.normalize();

	//Velocity.x() = Velocity.y() = speed;

	isAlive = true;
	isPassable = false;

    Randomize_Points(_w, _h, _n);
    _collide = c;
	_collide->Attach(this);

}

Comet::~Comet() {
	glDisableClientState(GL_VERTEX_ARRAY);
	vertVec.clear();
	_collide->Detach(this);
}

void Comet::Draw() {
	if (isAlive) 
    	Render(r, g, b, a);
}

void Comet::Logic() {
    if (CheckCollision())
        isAlive = false;
	angle += speed*1.5;
	Position.x() -= Direction.x()+Velocity.x();
	Position.y() -= Direction.y()+Velocity.y();

    if (inBounds) {
    	if (Position.x() < 0) {
    		Position.x() = Window::Get_Surf()->w;
    	} else if (Position.y() < 0) {
    		Position.y() = Window::Get_Surf()->h;
    	} else if (Position.x() > Window::Get_Surf()->w) {
    		Position.x() = 0;
    	} else if (Position.y() > Window::Get_Surf()->h) {
    		Position.y() = 0;
    	}
    }
}

void Comet::Randomize_Points(int w, int h, int n) {
	int halfnum = n/2;
	GLfloat lastx = -(rand() % w/3), lasty = -(rand() % h/2);

	// Top half
	for (unsigned int i=0; i<halfnum*3; i+=3) {
		vertVec.push_back(lastx);
		vertVec.push_back(lasty);
		vertVec.push_back(Position.z());
		lastx += (rand() % w), lasty = -(rand() % h/2);
	}

	// Set to start on opposite side
	lastx = (rand() % w), lasty += h/2;

	// Bottom half
	for (unsigned int i=halfnum*3; i<n*3; i+=3) {
		vertVec.push_back(lastx);
		vertVec.push_back(lasty);
		vertVec.push_back(Position.z());
		lastx -= (rand() % w), lasty = (rand() % h/2);
	}
}

void Comet::Render(int r, int g, int b, int a) {
glPushMatrix();
	glTranslatef(Position.x(), Position.y(), Position.z());
	//glTranslatef(Position.x()+(r_Rect.w/2), Position.y()-(r_Rect.h/2), Position.z());
	glRotatef(angle, 0, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertVec[0]);
    glColor4f(r, g, b, a);
	glDrawArrays(GL_LINE_LOOP, 0, n);
	glFlush();
glPopMatrix();
}

void Comet::Handle_Events() {}

void Comet::Update(Subject* ChangedSubject) {
	if (ChangedSubject != _collide) {
		_collide = static_cast<ICollide*>(ChangedSubject);
	}
}

void Comet::SetWrap(const bool isWrap) {
    inBounds = isWrap;
}

#include "comet.h"

Comet::Comet(ICollide* c, float _x, float _y, float _w, float _h, int _n, float vel, Vectorf& _vec, int _r, int _g, int _b, int _a) {
	Position.x() = _x, Position.y() = _y, r_Rect.w = _w, r_Rect.h = _h;
	r = _r, g = _g, b = _b, a = _a, n = _n;
	Position.z() = angle = 0;
	speed = Utility::UGen_Random(0.1, 1.0);
	radius = 5;
    centerx = Position.x()+r_Rect.w/2;
	centery = Position.y()+r_Rect.h/2;

	layer = 2;
	// Vector Subtraction gives us the vectors we need to shoot the comet at the player just once though
	Direction.x() = Position.x() - _vec.x();
	Direction.y() = Position.y() - _vec.y();
	Direction.normalize();

	Velocity.x() = speed;
	Velocity.y() = speed;

	isAlive = true;
	isPassable = false;

    Randomize_Points(Position.x(), Position.y(), _w, _h, _n);
    _collide = c;
	_collide->Attach(this);

}

Comet::~Comet() {
	glDisableClientState(GL_VERTEX_ARRAY);
	/*while(!vertVec.empty()) {
		vertVec.back();
		vertVec.pop_back();
	}*/
	vertVec.clear();
	_collide->Detach(this);
}

void Comet::Draw() {
	if (isAlive) 
    	Render(r, g, b, a);
}

void Comet::Logic() {
	angle += speed*1.5;
	//Velocity.x() *= 3.14159/180;
	//Velocity.y() *= 3.14159/180;
	//Position.x() -= Direction.x()/*+Velocity.x()*/;
	//Position.y() += Direction.x()/*+Velocity.x()*/;
	/*Position.x() += speed * sinf(Velocity.x());
	Position.y() -= speed * cosf(Velocity.y());*/
    /*centerx = Position.x()+r_Rect.w/2;
	centery = Position.y()+r_Rect.h/2;*/
}

void Comet::Randomize_Points(float x, float y, int w, int h, int n) {
	int halfnum = n/2;
	GLfloat lastx = 0, lasty = 0;

	// Top half
	for (unsigned int i=0; i<halfnum*3; i+=3) {
		lastx += (rand() % 1 + 10), lasty += (rand() % h/2);
		vertVec.push_back(lastx);
		vertVec.push_back(lasty);
		vertVec.push_back(Position.z());
	}

	// Set to start on opposite side
	lastx = w, lasty += h/2;

	// Bottom half
	for (unsigned int i=halfnum*3; i<n*3; i+=3) {
		lastx -= (rand() % 1 + 20), lasty = (rand() % h + h/2);
		vertVec.push_back(lastx);
		vertVec.push_back(lasty);
		vertVec.push_back(Position.z());
	}
}

void Comet::Render(int r, int g, int b, int a) {
glPushMatrix();
	glTranslatef(Position.x(), Position.y(), Position.z());
	glRotatef(angle, 0, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertVec[0]);
    glColor4f(r, g, b, a);
	//glDrawArrays(GL_LINE_LOOP, 0, n);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-5, -5, 0); glVertex3f(0, -3, 0); glVertex3f(5, -4, 0);
		glVertex3f(5, 5, 0); glVertex3f(0, 3, 0); glVertex3f(5, 4, 0);
	glEnd();
	glFlush();
glPopMatrix();
}

void Comet::Handle_Events() {}

void Comet::Update(Subject* ChangedSubject) {
	if (ChangedSubject != _collide) {
		_collide = static_cast<ICollide*>(ChangedSubject);
	}
}

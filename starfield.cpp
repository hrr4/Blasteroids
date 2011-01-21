#include "starfield.h"

Starfield::Starfield() {
	r_Rect.x = points = r_Rect.y = Position.z() = a = 0;
	points = Utility::UGen_Random(20.0, 100.0);

	r_Rect.w = Window::Get_Surf()->w;
	r_Rect.h = Window::Get_Surf()->h;

	/*xVec = rand() %  2;
	yVec = rand() %  2;*/

	RandomizePoints(r_Rect.x, r_Rect.y, r_Rect.w, r_Rect.h, points*3);
}

Starfield::~Starfield() {
    vertVec.clear();
}

void Starfield::Draw() {
	int offset = 20, tempTicks = SDL_GetTicks()+offset, test = SDL_GetTicks();
    if (tempTicks > SDL_GetTicks()) {
        a = Utility::UGen_Random(0.0, 1.0);
        tempTicks = (SDL_GetTicks()-FPS::deltaTicks)+offset;
	}
    Render();
}

void Starfield::Logic() {
	if ((FPS::Get_Ticks() / 1000.f)) {
		//a = rand() % 100;
	/*
    	if (((r_Rect.x + r_Rect.w) > Window::Get_Surf()->w) || r_Rect.x < 0) {
    		xVec *= -1;
    	} else if (r_Rect.y < 0) {
    		yVec *= -1;
    	}

		x += xVec * (FPS::Get_Ticks() / 5.f);
    	y += yVec * (FPS::Get_Ticks() / 5.f);
		r_Rect.x = static_cast<int>(x);
		r_Rect.y = static_cast<int>(y);
		*/
	}
}

void Starfield::RandomizePoints(Sint16& x, Sint16& y, Uint16& w, Uint16& h, int n) {
	for (unsigned int i=0; i < n; i+=3) {
		vertVec.push_back(static_cast<float>(rand() % w));
		vertVec.push_back(static_cast<float>(rand() % h));
		vertVec.push_back(Position.z());
	}
}

void Starfield::Render() {
glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertVec[0]);
    glColor4f(1, 1, 1, a);
	glDrawArrays(GL_POINTS, 0, points);
	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();
glPopMatrix();
}


void Starfield::Handle_Events() {}
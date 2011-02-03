#include "starfield.h"

Starfield::Starfield() : starVec((rand() % 200) + 20) {}

Starfield::~Starfield() {
    starVec.clear();
}

void Starfield::Draw() {
    for (int i = 0; i < starVec.size(); ++i) {
        glPushMatrix();
        glColor4f(1, 1, 1, starVec[i].a);
        glBegin(GL_POINTS);
            glVertex3f(starVec[i].Position.x(), starVec[i].Position.y(), 0);
        glEnd();
        glPopMatrix();
    }
}

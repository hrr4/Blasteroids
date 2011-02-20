#include "IParticle.h"

IParticle::IParticle() {}

IParticle::~IParticle() {}

void IParticle::createParticleSet(formationType _type, float _x, float _y, float _intensity, float _time) {
    switch(_type) {
    case radialOut:
        for (float angle = 0.1f; angle < _intensity*10+(rand() % 1 + 50); angle+=_intensity) {
        		tempSpeed = Utility::UGen_Random(0.5, 1.5);
    
            tempPosition.x() = ((rand() % 20) + sinf(angle)) + _x;
            tempPosition.y() = ((rand() % 20) + cosf(angle)) + _y;
    
        	  tempVelocity.x() = tempSpeed * sinf(angle);
        	  tempVelocity.y() = tempSpeed * cosf(angle);
    
        		tempHeading = atan2f(tempVelocity.y(), tempVelocity.x())*Utility::PI;

            particleVec.push_back(Particle(tempPosition, tempVelocity, _time*(rand() % 1 + 10), angle, tempHeading, tempSpeed));
        }
    }
}

void IParticle::updateParticleSet() {
  for (int i = 0; i < particleVec.size(); ++i) {
    float tempHeading = particleVec[i].heading, tempSpeed = particleVec[i].speed;
      if (particleVec[i].age >= 0) {
            particleVec[i].pos.x() += tempSpeed * sinf(tempHeading);
            particleVec[i].pos.y() += tempSpeed * cosf(tempHeading);

            particleVec[i].age -= 0.1;
        } else {
          particleVec.erase(particleVec.begin() + i);
        }
    }
}

void IParticle::drawParticleSet() {
    for (int i = 0; i < particleVec.size(); ++i) {
        glPushMatrix();
        glColor4f(1, 1, 1, particleVec[i].age);
            glBegin(GL_POINTS);
                glVertex3f(particleVec[i].pos.x(), particleVec[i].pos.y(), 0);
            glEnd();
        glPopMatrix();
    }
}

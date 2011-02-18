#include "IParticle.h"

IParticle::IParticle() {}

IParticle::~IParticle() {}

void IParticle::createParticleSet(formationType _type, float _x, float _y, float _intensity, float _time) {
    int testTimes = (rand() % 20), test= 0;
    float tempHeading, tempSpeed;
    Vectorf tempVelocity;
    switch(_type) {
    case radialOut:
      while (test < testTimes) {
        for (float angle = 0.1f; angle < 2 * Utility::PI; angle+=_intensity) {
        		tempSpeed = Utility::UGen_Random(0.5, 1.5);
    
            tempPosition.x() = ((rand() % 20) + sinf(angle)) + _x;
            tempPosition.y() = ((rand() % 20) + cosf(angle)) + _y;
    
        	  tempVelocity.x() = tempSpeed * sinf(angle);
        	  tempVelocity.y() = tempSpeed * cosf(angle);
    
            if (tempVelocity.y() >= 0)
            		tempHeading = atanf(tempVelocity.x()/tempVelocity.y());
            else 
            		tempHeading = atanf(tempVelocity.x()/tempVelocity.y())+Utility::PI;

            particleVec.insert(new Particle(tempPosition, tempVelocity, _time*(rand() % 1 + 10), angle, tempHeading, tempSpeed));
            /*particleMap.insert(std::make_pair(totalID, new Particle(tempPosition, tempVelocity, _time*(rand() % 1 + 10), angle, tempHeading, tempSpeed)));*/
        }
        ++test;
      }
    }
}

void IParticle::updateParticleSet() {
  //pIt = particleMap.begin();
  while(pIt != particleMap.end()) {
      float tempHeading = pIt->second->heading, tempSpeed = pIt->second->speed;
      if (pIt->second->age >= 0) {
            pIt->second->pos.x() += tempSpeed * sinf(tempHeading);
            pIt->second->pos.y() += tempSpeed * cosf(tempHeading);

            pIt->second->age -= 0.1;
            ++pIt;
        } else {
            pIt = particleMap.erase(pIt);
            if (pIt != particleMap.end()) {
                ++pIt;
            }
        }
    }
}

void IParticle::drawParticleSet() {
    for (pIt = particleMap.begin(); pIt != particleMap.end(); ++pIt) {
        glPushMatrix();
        glColor4f(1, 1, 1, pIt->second->age);
            glBegin(GL_POINTS);
                glVertex3f(pIt->second->pos.x(), pIt->second->pos.y(), 0);
            glEnd();
        glPopMatrix();
    }
}

#include "IParticle.h"

int IParticle::totalID = 0;

IParticle::IParticle() {
    /*glVertexPointer(*/}

IParticle::~IParticle() {}

void IParticle::createParticleSet(formationType _type, float _x, float _y, float _intensity, float _time) {
    switch(_type) {
    case radialOut:
        for (float angle = 2.0f; angle < 2 * Utility::PI; angle+=_intensity) {
            float tempAngle = (angle * Utility::DEGTORAD);
            tempPosition.x() = sinf(tempAngle) + _x;
            tempPosition.y() = cosf(tempAngle) + _y;
            particleMap.insert(std::make_pair(totalID, new Particle(ParticleType::Create, 
                tempPosition, 10, tempAngle)));
        }
    }
    ++totalID;
}

// When would i ever draw just one id and not all of them?
// Should I not just use a pointer (if possible) to the x, y, of each particle?

/*void IParticle::drawParticleSet(int _id) {
    for (pIt = particleMap.begin(); pIt != particleMap.end(); ++pIt) {
        test = particleMap.equal_range(_id);
        for (pIt = test.first; pIt != test.second; ++pIt) {
            glPushMatrix();
                glBegin(GL_POINTS);
                    glVertex3f(pIt->second->pos.x(), pIt->second->pos.y(), 0);
                glEnd();
            glPopMatrix();
        }
    }
}*/

void IParticle::updateParticleSet() {
    for (pIt = particleMap.begin(); pIt != particleMap.end(); ++pIt) {
        if (!pIt->second->age <= 0) {
            float heading, speed = 2;
            pIt->second->vel.x() = speed * sinf(pIt->second->angle);
            pIt->second->vel.y() = speed * cosf(pIt->second->angle);
        	if (pIt->second->vel.y() >= 0)
        		heading = atanf(pIt->second->vel.x()/pIt->second->vel.y());
        	else 
        		heading = atanf(pIt->second->vel.x()/pIt->second->vel.y())+Utility::PI;
            pIt->second->pos.x() += speed * sinf(heading);
            pIt->second->pos.y() -= speed * cosf(heading);

            pIt->second->age -= 0.01;
        } else {
            // Erase = destroying iterator.... could be a problem yes? lol
           // particleMap.erase(pIt);
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

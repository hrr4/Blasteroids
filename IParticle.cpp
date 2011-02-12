#include "IParticle.h"

int IParticle::totalID = 0;

IParticle::IParticle() {
    /*glVertexPointer(*/}

IParticle::~IParticle() {}

void IParticle::createParticleSet(formationType _type, float _x, float _y, float _intensity, float _time) {
    //float tempAngle = 0.0f;
    int tempID = totalID;
    switch(_type) {
    case radialOut:
        for (float angle = 0.0f; angle < 2 * Utility::PI; angle+=_intensity) {
            tempPosition.x() = sinf(angle);
            tempPosition.y() = cosf(angle);
            particleMap.insert(std::make_pair(tempID, new Particle(ParticleType::Create, tempPosition, 10)));
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
            // Here we update velocity? and we should probably add that to the position.....? something
            //pIt->second->pos.x() 
            pIt->second->vel.x() = 2;
            pIt->second->vel.y() = 2;
            pIt->second->pos.x() += pIt->second->vel.x();
            pIt->second->pos.y() += pIt->second->vel.y();

            pIt->second->age -= 0.0001;
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

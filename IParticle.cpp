#include "IParticle.h"

int IParticle::totalID = 0;

IParticle::IParticle() {}

IParticle::~IParticle() {}

void IParticle::DrawExplosion(formationType _formation, float _intensity, float _fade, float _x, float _y, particleType _type) {
    switch(_formation) {
    case radialOut:
        for (int i = 0; i < (_intensity*100); ++i) {

        }
    }
}
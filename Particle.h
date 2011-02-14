#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL_opengl.h>
#include "vector.h"

enum ParticleType {Create, Update};

struct Particle {
    Particle(ParticleType _type, Vectorf _pos, float _lifeSpan, float _angle, int _size = 1);

    Vectorf pos, vel;
    int color, size;
    float age, lifeSpan, angle;
    ParticleType type;
};

#endif
#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL_opengl.h>
#include "vector.h"

enum ParticleType {Create, Update};

struct Particle {
    Vectorf pos, vel;
    int age, lifeSpan, color, size;
};

#endif
#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL_opengl.h>
#include "vector.h"

struct Particle {
    Particle(Vectorf _pos, Vectorf _vel, float _lifeSpan, float _angle, float _heading, float _speed, int _size = 1);

    Vectorf pos, vel;
    int color, size;
    float age, lifeSpan, angle, heading, speed;
};

#endif

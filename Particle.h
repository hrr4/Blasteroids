#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL_opengl.h>

struct Particle {
    enum drawType {pPoint, pCircle, pSquare, pTriangle};

    Particle(drawType _myType, int _size);
    ~Particle();

private:
    drawType p_myType;
};

#endif
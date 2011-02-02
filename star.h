#ifndef STAR_H
#define STAR_H

#include <SDL_opengl.h>
#include <vector>
#include "vector.h"
#include "window.h"

struct Star {
    Star();
    Vectorf Position;
    float a;
};

#endif
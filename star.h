#ifndef STAR_H
#define STAR_H

#include "Entity.h"
#include "fps.h"
#include <SDL_opengl.h>
#include <vector>
#include "Utility.h"
#include "vector.h"
#include "window.h"

struct Star {
    Star();
    Vectorf Position;
    float a;
};

#endif
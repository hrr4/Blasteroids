#include "emitter.h"

Emitter::Emitter(Collider* collider, float _x, float _y, float _interval) :
    myCollider(collider), x(_x), y(_y), Interval(_interval), maxTime(SDL_GetTicks()+_interval) {};

Emitter::~Emitter() {
    myCollider = 0;
    delete myCollider;
}

void Emitter::ChangeInterval(float newInterval) {
    Interval = newInterval;
}

void Emitter::Logic() {
    if (SDL_GetTicks() > maxTime) {
        EmitNew();
        maxTime = SDL_GetTicks() + Interval;
    }
}

Collider* Emitter::EmitNew() {
    myCollider->SetPosition(x, y);
    return myCollider;
}
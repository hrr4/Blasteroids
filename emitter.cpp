#include "emitter.h"

Emitter::Emitter() {}

Emitter::Emitter(Collider* collider, float _x, float _y, float _interval) :
    myCollider(collider), x(_x), y(_y), Interval(_interval), maxTime(SDL_GetTicks()+(_interval*100)) {};

Emitter::~Emitter() {
    myCollider = 0;
    delete myCollider;
}

void Emitter::ChangeInterval(float newInterval) {
    Interval = newInterval*100;
}

bool Emitter::NextEmit() {
    if (SDL_GetTicks() > maxTime) {
        maxTime = SDL_GetTicks() + (Interval*100);
        return true;
    }
    myCollider = 0;
    return false;
}

Collider* Emitter::EmitNew() {
    //delete myCollider;
    //*myCollider = new Comet();
    myCollider->SetPosition(x, y);
    return myCollider;
}
#ifndef EMITTER_H
#define EMITTER_H

#include "collider.h"
#include "comet.h"

class Emitter {
public:
    Emitter(Collider* collider, float _x, float _y, float _interval);
    Emitter();
    ~Emitter();
    void ChangeInterval(float newInterval);
    Collider* EmitNew();
    bool NextEmit();
private:
    Collider* myCollider;
    float x, y, Interval;
    int maxTime;
};

#endif
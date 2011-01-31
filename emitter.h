#ifndef EMITTER_H
#define EMITTER_H

#include "collider.h"

class Emitter {
public:
    Emitter(Collider* collider, float _x, float _y, float _interval);
    ~Emitter();
    void ChangeInterval(float newInterval);
    Collider* EmitNew();
    void Logic();
protected:
    Emitter();
private:
    Collider* myCollider;
    float x, y, Interval;
    int maxTime;
};

#endif
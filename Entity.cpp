#include "Entity.h"

Entity::~Entity() {}

Vectorf Entity::GetPosition() const {return Position;}

float Entity::GetRadius() const {return radius;}

float Entity::GetAngle() const {return angle;}

bool Entity::GetAlive() const {return isAlive;}

int Entity::GetLayer() const {return layer;}

void Entity::SetPosition(float _x, float _y) {
    Position.x() = _x;
    Position.y() = _y;
}
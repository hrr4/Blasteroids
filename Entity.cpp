#include "Entity.h"

Entity::~Entity() {}

// Getters
Vectorf Entity::GetPosition() const {return Position;}

float Entity::GetRadius() const {return radius;}

float Entity::GetAngle() const {return angle;}

bool Entity::GetAlive() const {return isAlive;}

int Entity::GetLayer() const {return layer;}

// Setters
void Entity::SetPosition(float _x, float _y) {
    Position.x() = _x;
    Position.y() = _y;
}

void Entity::SetAlive(bool _status) {isAlive = _status;}
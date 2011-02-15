#include "Particle.h"

Particle::Particle(Vectorf _pos, Vectorf _vel, float _lifeSpan, float _angle, float _heading, float _speed, int _size) :
  pos(_pos), age(_lifeSpan), lifeSpan(_lifeSpan), angle(_angle), heading(_heading), speed(_speed), vel(_vel) {}

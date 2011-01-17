#include "collider.h"

Collider::Collider() {}

Collider::~Collider() {}

bool Collider::CheckCollision() {
	// Actual collision checking done here.
	// 1. Find the nearest collider
	// 2. Check Radii regardless of distance..(Could be optimized)
	// 3. If Radii touch/overlap, test AABB.
	if (_collide->TestRadii(this, _collide->FindNearest(this)))
		//_collide->TestAABB(this);
		return true;
	return false;
}
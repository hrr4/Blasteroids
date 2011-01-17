#include "icollide.h"

class Collider : public Observer, public Entity {
public:
	virtual ~Collider();
	virtual bool CheckCollision();
protected:
	Collider();
	ICollide* _collide;
};

ICollide::~ICollide() {}

Collider* ICollide::FindNearest(Collider* c1) {
	float x1 = c1->GetPosition().x(), y1 = c1->GetPosition().y(), xClosest = 0, yClosest = 0;
	Collider* closestC = 0, *lastC = 0;
	if (_observers.size() > 1) {
    	std::list<Observer*>::iterator it;
    	for (it = _observers.begin(); it != _observers.end(); ++it) {
    		if (*it != c1) {
            	Collider* c = reinterpret_cast<Collider*>(*it);
        		if (c->GetLayer() != c1->GetLayer()) {
        			float xOldNear = xClosest;
        			float yOldNear = yClosest;
        			xClosest = abs(x1 - c->GetPosition().x());
        			yClosest = abs(y1 - c->GetPosition().y());
        			if (xClosest < xOldNear) {
        				xOldNear = xClosest; 
        				closestC = c;
        			}
        			if (yClosest < yOldNear) {
        				yOldNear = yClosest; 
        				closestC = c;
        			}
        			if (closestC == NULL) {
        				closestC = c;
        			}
    			}
    		}
    	}
	}
	if (closestC == 0) {
		return c1;
	} else {
    	return closestC;
	}
}

bool ICollide::TestRadii(Collider* c1, Collider* c2) {
	if (c1 != c2) {
    	const float TOUCH_DISTANCE = 0.00001;
    	float x1 = c1->GetPosition().x(), y1 = c1->GetPosition().y(), r1 = c1->GetRadius();
    	float x2 = c2->GetPosition().x(), y2 = c2->GetPosition().y(), r2 = c2->GetRadius();
    	float distance_squared, radii_squared;
    
    	//a^2 + b^2 = c^2
    	distance_squared = ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    
    	// Multiply rather than sqrt, faster
    	radii_squared = (r1 + r2)*(r1 + r2);
    
    	// Finally, conduct tests
    	if (-TOUCH_DISTANCE < radii_squared - distance_squared && radii_squared - distance_squared < TOUCH_DISTANCE) {
    		// Touching
    		return true;
    	} else if (radii_squared > distance_squared) {
    		// Overlapping
    		return true;
    	} else {
    		// Nothing
    		return false;
    	}
	} else {
		return false;
	}
}

bool ICollide::TestAABB(Collider* c1) {return false;}

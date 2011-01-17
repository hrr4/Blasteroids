#include "subject.h"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::Attach(Observer* o) {
	_observers.push_back(o);
}

void Subject::Detach(Observer* o) {
	_observers.remove(o);
}

void Subject::Notify() {
	std::list<Observer*>::iterator it;
	for (it = _observers.begin(); it != _observers.end(); ++it) {
    	Observer* o = *it;
		o->Update(this);
	}
}
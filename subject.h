#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "observer.h"

class Subject {
public:
	virtual ~Subject();

	void Attach(Observer*);
	void Detach(Observer*);
	void Notify();
protected:
	Subject();
	std::list<Observer*> _observers;
};

#endif
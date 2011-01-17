#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>

struct Event {
public:
	static SDL_Event* Get_Event();
private:
	static SDL_Event m_Event;
};

#endif
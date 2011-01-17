#include "event.h"

SDL_Event Event::m_Event;

SDL_Event* Event::Get_Event() {
	return &m_Event;
}
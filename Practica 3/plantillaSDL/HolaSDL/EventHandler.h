#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL_events.h>

class EventHandler
{
public:
	// gestiona un evento
	virtual void handleEvent(const SDL_Event& event) = 0;
};

#endif
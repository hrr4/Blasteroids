#include "fps.h"

int FPS::deltaTicks = 0;

FPS::FPS() {
	startTicks=0, pausedTicks=0;
	paused=false, started=false;
}

void FPS::Start() {
	started = true;
	paused = false;
	FPS::deltaTicks = SDL_GetTicks();
}

void FPS::Stop() {
	started = false;
	paused = false;
	FPS::deltaTicks = 0;
}

int FPS::Get_Ticks() {
    return SDL_GetTicks() - FPS::deltaTicks;
}

void FPS::Pause() {
	if ((started == true) && (paused == false)) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void FPS::Unpause() {
	if (paused == true) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

bool FPS::Is_Started() {
	return started;
}

bool FPS::Is_Paused() {
	return paused;
}
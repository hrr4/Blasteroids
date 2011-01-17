#ifndef FPS_H
#define FPS_H

#include <SDL.h>

class FPS {
public:
	FPS();
	void Start();
	void Stop();
	void Pause();
	void Unpause();
	static int Get_Ticks();
	bool Is_Started(), Is_Paused();
	static int deltaTicks;
private:
	int startTicks, pausedTicks;
	bool started, paused;
};
#endif

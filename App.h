#ifndef APP_H
#define APP_H

#include "window.h"
#include "gamescreen.h"
#include "intro.h"
#include "title.h"
#include "fps.h"
#include "level.h"
#include <SDL.h>
#include <SDL_image.h>
#include <sstream>
#include <SDL_opengl.h>
#include <random>
#include <time.h>

class App {
public:
	App();
	~App();
	void Loop();
	bool Get_Running() const;
private:
	bool initGL();
	void Query_GameScreen();
	void Set_GameScreen(StateManager::Global currentGlobal);
    Window* winmain;
	IGameScreen* activeScreen;
	StateManager manager;
	FPS delta;
	bool isRunning, levelNum;
    unsigned long int next_tick;
};

#endif
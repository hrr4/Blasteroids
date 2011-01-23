#include "App.h"

App::App() {
	srand(time(0));
    winmain = new Window(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL);
	activeScreen = new Title();
	delta.Start();
	SDL_Init(SDL_INIT_EVERYTHING);
	initGL();}

App::~App() {
	delete winmain, activeScreen;
}

void App::Loop() {
    next_tick = SDL_GetTicks () + 10;
	while (manager.Get_GlobalState() != StateManager::Global_Exit) {
		//delta.Start();
        if (SDL_GetTicks() > next_tick ) {
            next_tick = SDL_GetTicks() + 10;
    		activeScreen->Handle_Events();
    		activeScreen->Logic();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		activeScreen->Draw();
		SDL_GL_SwapBuffers();
		Query_GameScreen();
	}
}

void App::Query_GameScreen() {
	if (activeScreen->Get_State() != StateManager::Child_Null) {
		Set_GameScreen(manager.Query_State(activeScreen->Get_State()));
	}
}

void App::Set_GameScreen(StateManager::Global nextGlobal) {
	switch(nextGlobal) {
	case StateManager::Global_Intro :
    	delete activeScreen;
		activeScreen = new Intro();
		manager.Set_GlobalState(nextGlobal);
		break;
	case StateManager::Global_Title :
    	delete activeScreen;
		activeScreen = new Title();
		manager.Set_GlobalState(nextGlobal);
		levelNum = 0;
		break;
	case StateManager::Global_Level :
        switch(manager.Get_GlobalState()) {
		case StateManager::Global_Title :
        	delete activeScreen;
    		activeScreen = new Level(levelNum);
            break;
		case StateManager::Global_Level :
        	delete activeScreen;
            activeScreen = new Level(++levelNum);
            break;
		} 
		/*if (currLevel == global::numLevels) {
            activeScreen = new Title();
			//currLevel = 0;
        }*/
		manager.Set_GlobalState(nextGlobal);
		break;
	case StateManager::Global_Exit :
    	delete activeScreen;
		// FIX: Could expand to actually ask user wherever they're at if they
		//			really want to quit. But for now, we're just gonna exit based
		//			on what the Child wants..
		activeScreen = new Title();
		manager.Set_GlobalState(StateManager::Global_Exit);
		break;
	}
	manager.ResetNext();
}

bool App::initGL() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Window::Get_Surf()->w, Window::Get_Surf()->h, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA/*GL_ONE*/);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	if (glGetError() != GL_NO_ERROR)
		return false;
	return true;
}
#include "App.h"

App::App() {
	srand(time(0));
    winmain = new Window(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL);
	activeScreen = new Title();
	delta.Start();
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	initGL();
}

App::~App() {
	delete winmain, activeScreen;
}

void App::Loop() {
	while (StateManager.Get_GlobalState() != StateManager::Global_Exit) {
		delta.Start();
		activeScreen->Handle_Events();
		activeScreen->Logic();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		activeScreen->Draw();
		SDL_GL_SwapBuffers();
		Query_GameScreen();
	}
}

void App::Query_GameScreen() {
	if (activeScreen->Get_State() != StateManager::Child_Null) {
		Set_GameScreen(StateManager.Query_State(activeScreen->Get_State()));
	}
}

void App::Set_GameScreen(StateManager::Global nextGlobal) {
	switch(nextGlobal) {
	case StateManager::Global_Intro :
    	delete activeScreen;
		activeScreen = new Intro();
		StateManager.Set_GlobalState(nextGlobal);
		break;
	case StateManager::Global_Title :
    	delete activeScreen;
		activeScreen = new Title();
		StateManager.Set_GlobalState(nextGlobal);
		//currLevel = 0;
		break;
	case StateManager::Global_Level :
		switch(activeScreen->Get_State()) {
		case StateManager::Global_Title :
        	delete activeScreen;
    		//activeScreen = new Level(currLevel);
            break;
		case StateManager::Global_Level :
        	delete activeScreen;
            //activeScreen = new Level(++currLevel);
            break;
		} 
		/*if (currLevel == global::numLevels) {
            activeScreen = new Title();
			//currLevel = 0;
        }*/
		StateManager.Set_GlobalState(nextGlobal);
		break;
	case StateManager::Global_Exit :
    	delete activeScreen;
		// FIX: Could expand to actually ask user wherever they're at if they
		//			really want to quit. But for now, we're just gonna exit based
		//			on what the Child wants..
		activeScreen = new Title();
		StateManager.Set_GlobalState(StateManager::Global_Exit);
		break;
	}
	StateManager.ResetNext();
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
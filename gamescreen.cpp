#include "gamescreen.h"

IGameScreen::IGameScreen() {
    //fe_p = fe.get();
	currentChild = StateManager::Child_Null;
	srand(time(NULL));
    /*fe_p = new FontEngine("04b_11.ttf");
    fe_p->AddFont("FreeSans.ttf");*/
    fe = new FontEngine("04b_11.ttf");
    fe->AddFont("FreeSans.ttf");
}

IGameScreen::~IGameScreen() {
    /*if (!fe_p)
        delete fe_p;*/
}

StateManager::Child IGameScreen::Get_State() {
	return currentChild;
}

void IGameScreen::Set_State(StateManager::Child tempChild) {
	currentChild = tempChild;
}

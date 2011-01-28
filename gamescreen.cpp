#include "gamescreen.h"

IGameScreen::IGameScreen() {
	currentChild = StateManager::Child_Null;
	srand(time(NULL));
    fe = new FontEngine("04b_11.ttf");
    fe->AddFont("FreeSans.ttf");
}

IGameScreen::~IGameScreen() { }

StateManager::Child IGameScreen::Get_State() {
	return currentChild;
}

void IGameScreen::Set_State(StateManager::Child tempChild) {
	currentChild = tempChild;
}

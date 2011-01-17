#include "gamescreen.h"

IGameScreen::IGameScreen() {
	currentChild = StateManager::Child_Null;
	srand(time(NULL));
}

IGameScreen::~IGameScreen() {}

StateManager::Child IGameScreen::Get_State() {
	return currentChild;
}

void IGameScreen::Set_State(StateManager::Child tempChild) {
	currentChild = tempChild;
}

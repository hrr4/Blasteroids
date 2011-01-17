#include "statemanager.h"

StateManager::StateManager() {
	currentGlobal = Global_Intro;
	currentChild = Child_Null;	
}

void StateManager::Set_GlobalState(Global nextGlobal) {
	currentGlobal = nextGlobal;
}

void StateManager::ResetNext() {
	nextGlobal = Global::Global_Null;
}

StateManager::Global StateManager::Get_GlobalState() const {
	return currentGlobal;
}

StateManager::Global StateManager::Query_State(Child currentChild) {
	if (currentChild != Child::Child_Null) {
    	switch (currentChild) {
    	case Child::Child_Restart :
			nextGlobal = currentGlobal;
			break;
		case Child::Child_Quit :
			nextGlobal = Global::Global_Exit;
			break;
		case Child::Child_Exit :
			nextGlobal = Global::Global_Title;
			break;
		case Child::Child_Success :
			if (currentGlobal == Global::Global_Level) {
				nextGlobal = currentGlobal;
			} else {
    			nextGlobal = static_cast<Global>(currentGlobal + 1);
			}
			break;
		}
	return nextGlobal;
    }
}

StateManager::Child StateManager::Get_ChildState() const {
	return currentChild;
}

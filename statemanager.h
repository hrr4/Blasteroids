#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager {
// Enums
public:
	enum Global {Global_Null, Global_Intro, Global_Title, Global_Level, Global_Exit};
	enum Child {Child_Restart, Child_Quit, Child_Null, Child_Exit, Child_Success};
 
public:
	StateManager();
	Global Get_GlobalState() const;
	Child Get_ChildState() const;
	Global Query_State(Child currentChild);
	void ResetNext();
	void Set_GlobalState(Global nextGlobal);

private:
	Child /*nextChild,*/ currentChild;
	Global nextGlobal, currentGlobal;
};

#endif
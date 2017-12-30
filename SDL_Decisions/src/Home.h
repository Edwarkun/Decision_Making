#pragma once
#include "State.h"

class Home : public State {
public:
	static State* instance;
	Home();
	void Enter(Agent*);
	void Update(Agent*, float);
	void Exit(Agent*);
};
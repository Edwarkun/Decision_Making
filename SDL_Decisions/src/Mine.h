#pragma once
#include "State.h"

class Mine : public State {
public:
	static State* instance;
	Mine();
	void Enter(Agent*);
	void Update(Agent*, float);
	void Exit(Agent*);
};

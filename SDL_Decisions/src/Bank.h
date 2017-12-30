#pragma once
#include "State.h"

class Bank : public State {
public:
	static State* instance;
	float counter = 0;
	Bank();
	void Enter(Agent*);
	void Update(Agent*, float);
	void Exit(Agent*);
};
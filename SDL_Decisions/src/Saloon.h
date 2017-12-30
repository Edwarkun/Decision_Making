#pragma once
#include "State.h"

class Saloon : public State {
public:
	static State* instance;
	float counter;
	Saloon();
	void Enter(Agent*);
	void Update(Agent*, float);
	void Exit(Agent*);
};
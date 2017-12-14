#pragma once
#include "State.h"

class Saloon : public State {
public:
	Saloon();
private:
	void Enter();
	void Update();
	void Exit();
};
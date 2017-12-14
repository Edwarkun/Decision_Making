#pragma once
#include "State.h"

class Mine : public State {
public:
	Mine();
private:
	void Enter();
	void Update();
	void Exit();
};
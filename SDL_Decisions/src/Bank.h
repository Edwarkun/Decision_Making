#pragma once
#include "State.h"

class Bank : public State {
public:
	Bank();
private:
	void Enter();
	void Update();
	void Exit();
};
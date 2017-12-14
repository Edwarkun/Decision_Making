#pragma once
#include "Vector2D.h"
#include "Path.h"
#include "Node.h"
#include "Agent.h"

class Agent;
class State {
private:
	State* instance = nullptr;
public:
	virtual void Enter(Agent*, std::vector<Node*>) = 0;
	virtual void Update(Agent*) = 0;
	virtual void Exit(Agent*) = 0;
};

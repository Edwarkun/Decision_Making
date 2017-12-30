#pragma once
#include "Vector2D.h"
#include "Path.h"
#include "Node.h"
#include "Agent.h"
#include "Text.h"

class Agent;

class State {
public:
	bool movedToLocation;
	virtual void Enter(Agent*) = 0;
	virtual void Update(Agent*, float) = 0;
	virtual void Exit(Agent*) = 0;
};

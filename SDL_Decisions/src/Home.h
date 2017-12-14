#pragma once
#include "State.h"

class Home : public State {
public:
	static State* stateInstance;
	Vector2D HomeVector;
	Home();
private:
	static State* Instance();
	void Enter(Agent* agent, std::vector<Node*> grid);
	void Update(Agent* agent);
	void Exit(Agent* agent);
};
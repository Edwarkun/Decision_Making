#include "Home.h"

State * Home::stateInstance = 0;

Home::Home() {
	HomeVector = Vector2D(34 * 32, 21 * 32);
}
void Home::Enter(Agent* agent, std::vector<Node*> grid) {
	//Go home
	Path path = agent->FindPath(grid, Vector2D(64, 64), HomeVector);
}
void Home::Update(Agent* agent) {
	//Update the variables
	agent->thirst++;
	agent->tiredness--;
	if (agent->thirst > agent->limit_thirst) {
		//Go to saloon
		agent->ChangeState(Saloon);

	} else if (agent->tiredness < 10) {
		//Go to mine
		agent->ChangeState(Mine);
	}

}
void Home::Exit(Agent* agent) {
	
}
State* Home::Instance() {
	if (stateInstance == 0) {
		stateInstance = new Home();
	}
	return stateInstance;
}
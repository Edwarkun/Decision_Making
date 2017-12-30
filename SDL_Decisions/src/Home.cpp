#include "Home.h"

State* Home::instance = new Home;

Home::Home() {
	instance = this;
}
void Home::Enter(Agent* agent) {
	movedToLocation = false;
	agent->setTarget(Vector2D(16 + 32 * 33, 16 + 32 * 20));
	agent->stateNotification = "Going to rest and sleep";
}
void Home::Update(Agent* agent, float delta) {
	if (!movedToLocation) {
		//Check if it arrived to the mine
		if ((agent->getPosition() - agent->getTarget()).Length() < 32) {
			movedToLocation = true;
			agent->stateNotification = "ZZZZZZZZZZ";
		}
		agent->tiredness += delta / 6;
		agent->thirst += delta / 6;
	}
	else {
		agent->tiredness -= delta * 2;
		if (agent->tiredness < 0.4) {
			//Check the priorities: Saloon > Bank > Mine
			if ((agent->total_coins + agent->coins) > agent->drink_cost && agent->thirst > agent->limit_thirst) {
				//Go to drink
				agent->ChangeState(State_Saloon);
			}
			else if (agent->coins >= agent->max_coins) {
				agent->ChangeState(State_Bank);
			}
			else {
				agent->ChangeState(State_Mine);
			}
		}
		agent->thirst += delta / 20;

	}
}
void Home::Exit(Agent* agent) {
	
}

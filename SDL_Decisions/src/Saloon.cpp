#include "Saloon.h"

State* Saloon::instance = new Saloon;

Saloon::Saloon() {
	instance = this;
}
void Saloon::Enter(Agent* agent) {
	movedToLocation = false;
	counter = 0;
	agent->setTarget(Vector2D(16 + 32 * 19, 16 + 32 * 20));
	agent->stateNotification = "Going to the saloon to drink";
}
void Saloon::Update(Agent* agent, float delta) {
	if (!movedToLocation) {
		//Check if it arrived to the mine
		if ((agent->getPosition() - agent->getTarget()).Length() < 32) {
			movedToLocation = true;
			agent->stateNotification = "Drinking at the saloon";
		}
		agent->tiredness += delta / 6;
		agent->thirst += delta / 6;
	}
	else {
		if (agent->thirst <= 2.44f || agent->total_coins + agent->coins <= 0) {
			//Check the priorities: Home > Bank > Mine
			if (agent->tiredness > agent->limit_tiredness) {
				agent->ChangeState(State_Home);
			}
			else if (agent->coins >= agent->max_coins) {

				agent->ChangeState(State_Bank);
			}
			else {
				agent->ChangeState(State_Mine);
			}
		}
		else {
			if (counter > 1.5f) {
				counter -= 1.5f;
				agent->thirst -= 2.44;
				if (agent->total_coins <= 0) {
					agent->coins--;
				}
				else {
					agent->total_coins--;
				}
			}
			else {
				counter += delta;
			}
		}
		agent->tiredness += delta / 9;
	}
}
void Saloon::Exit(Agent* agent) {

}
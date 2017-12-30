#include "Bank.h"


State* Bank::instance = new Bank;

Bank::Bank() {
	instance = this;
}
void Bank::Enter(Agent* agent) {
	movedToLocation = false;
	agent->setTarget(Vector2D(16 + 32 * 5, 16 + 32 * 20));
	counter = 0;
	agent->stateNotification = "Going to the bank to store money";
}
void Bank::Update(Agent* agent, float delta) {
	if (!movedToLocation) {
		//Check if it arrived to the mine
		if ((agent->getPosition() - agent->getTarget()).Length() < 32) {
			movedToLocation = true;
			agent->stateNotification = "Storing Money...";
		}

		agent->tiredness += delta / 6;
		agent->thirst += delta / 6;
	}
	else {

		counter += delta;
		if (counter > 1.5) {
			agent->coins--;
			agent->total_coins++;
			counter -= 1.5;
		}
		if (agent->coins == 0) {
			//Check the priorities: Drink > Home > Mine
			if (agent->thirst > agent->limit_thirst) {
				//Go to drink
				agent->ChangeState(State_Saloon);
			}
			else if (agent->tiredness > agent->limit_tiredness) {
				agent->ChangeState(State_Home);
			}
			else {
				agent->ChangeState(State_Mine);
			}
		}
		agent->thirst += delta / 9;
	}
}
void Bank::Exit(Agent* agent) {

}
#include "Mine.h"

State* Mine::instance = new Mine;

Mine::Mine() {
	instance = this;
}
void Mine::Enter(Agent* agent) {
	agent->setTarget(Vector2D(16 + 32 * 19,16 + 32 * 6));
	movedToLocation = false;
	agent->stateNotification = "Heading to the mine";
}
void Mine::Update(Agent* agent, float delta) {
	//It has reached the mine
	if (!movedToLocation) {
		//Check if it arrived to the mine
		if ((agent->getPosition() - agent->getTarget()).Length() < 32) {
			movedToLocation = true;
			agent->setTarget(agent->GetGoldNuggetPosition());
			agent->stateNotification = "Mining...";
		}
		
	}
	else {
		//While mining the agent gets even more tired and thirsty
		agent->tiredness += delta / 4;
		agent->thirst += delta / 6;

		//The agent has collected a gold nugget
		if (Vector2D(agent->getPosition() - agent->GetGoldNuggetPosition()).Length() < 32) {
			agent->coins++;
			agent->SetGoldNuggetPosition(Vector2D(48 + (int)(rand() % 38) * 32, 48 + (int)(rand() % 4) * 32));
			//Check if the miner has other needs, if he does then swap the state
			//Priority -> Drink / Sleep / Store
			if ((agent->total_coins + agent->coins) > agent->drink_cost && agent->thirst > agent->limit_thirst) {
				//Go to drink
				agent->ChangeState(State_Saloon);
			}
			else if (agent->tiredness > agent->limit_tiredness) {
				agent->ChangeState(State_Home);
			}
			else if (agent->coins >= agent->max_coins) {
				agent->ChangeState(State_Bank);
			}
			else {
				agent->setTarget(agent->GetGoldNuggetPosition());
			}

		}
		//the miner gets tired and thirsty while in this state
	}
	agent->tiredness += delta / 6;
	agent->thirst += delta / 6;

	//agent->ChangeState(State_Saloon);
}
void Mine::Exit(Agent* agent) {

}

/*#include "Astrella.h"

#include <iostream>
#include<vector>
#include<queue>

using namespace std;
vector<goap::Action>goap::AlgoritmeA::Astrella(const WorldState& _startState, const WorldState& _goalState, const vector<Action>& actions) {
	if (_startState.meetsGoal(_goalState)) {//si el incialSatate es el mateix que el goalState
		return vector<goap::Action>();//
	}

	priority_queue<Node&>frontier;
	unordered_map<Node*, Node*> cameFrom;
	unordered_map<Node*, int> costSoFar;
	

	Node *start = nullptr;
	frontier.emplace(start);
	cameFrom[start] = nullptr;
	costSoFar[start] = 0;

	while (frontier.size()) {
		Node* current = frontier.top;
		if (current->ws == _goalState) {
			while (current != start) {//if current != node.ws.init
				current->ws.getVariablesMon;
				cameFrom[start] = current;
			}
		}

		//comprovar cada node accesible desde current, a on podem anar?
		for (const auto& i : actions) {
			if (i.operableOn(current->ws)) {//si les precondcision de i sobre current coincideixen
				Node tmp(current, current->g, current->h, current->parentId, i);
				goap::WorldState seguent = i.actOn(current->ws);//JUST DO IT
			}
		}
	}

	/*while (startState.size() > 0) {
		Node *current = frontier.top();
	}
}*/
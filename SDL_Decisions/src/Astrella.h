/*#pragma once
#include "Accio.h"
#include "WorldState.h"
#include "NodeGOAP.h"
#include <vector>

using namespace std;

namespace goap {
	class AlgoritmeA
	{
		vector<goap::Node> startState;
		vector<goap::Node> goalState;
		//goap::WorldState startState;
		//goap::WorldState goalState;

		vector<goap::Action> Astrella(const WorldState& _startNode, const WorldState& _goalNode, const vector<Action>& actions);

		bool comprovaWorld(const goap::WorldState& ws) const;//comprova si el worldState donat el conte algun node de la llista

	};
}*/
#include "WorldState.h"

using namespace std;
goap::WorldState::WorldState(const string _name) : priority(0), name(_name) {}

void goap::WorldState::setVariablesMon(const int varId, const bool value) {
	variablesMon[varId] = value;
}

bool goap::WorldState::getVariablesMon(const int varId) const {
	return variablesMon.at(varId);
}

bool goap::WorldState::meetsGoal(const WorldState& goalState)const {
	for (const auto& i : goalState.variablesMon) {
		try {
			if(variablesMon.at(i.first) != i.second){
				return false;
			}
		}
		catch (const out_of_range&) {
			return false;
		}
	}
	return true;

}

int goap::WorldState::distanceTo(const WorldState& goalState) const {
	int result = 0;

	for (const auto& i : goalState.variablesMon) {
		auto j = variablesMon.find(i.first);
		if (j == end(variablesMon) || j->second != i.second) {
			result++;
		}
	}

	return result;
}

bool goap::WorldState::operator==(const WorldState& other)const {
	return(variablesMon == other.variablesMon);
}
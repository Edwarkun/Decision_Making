#include "NodeGOAP.h"
#include<iostream>

int goap::NodeGOAP::lastId = 0;

goap::NodeGOAP::NodeGOAP() :g(0), h(0) 
{
	id = ++lastId;
}

goap::NodeGOAP::NodeGOAP(const WorldState state, int _g, int _h, int _parenId, const Action* _action) :
	ws(state), g(_g), h(_h), parentId(_parenId), action(_action)
{
	id = ++lastId;
}

bool goap::operator<(const goap::NodeGOAP& lhs, const goap::NodeGOAP& rhs) {
	return lhs.totalCost() < rhs.totalCost();
}
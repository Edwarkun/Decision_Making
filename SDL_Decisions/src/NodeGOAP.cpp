#include "Node.h"
#include<iostream>

using namespace std;

int goap::Node::lastId = 0;

goap::Node::Node() :g(0), h(0) 
{
	id = ++lastId;
}

goap::Node::Node(const WorldState state, int _g, int _h, int _parenId, const Action* _action) :
	ws(state), g(_g), h(_h), parentId(_parenId), action(_action)
{
	id = ++lastId;
}

/*bool goap::operator<(const goap::Node& left, const goap::Node right) {
	return left.totalCost() < right.totalCost();
}*/
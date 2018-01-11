#pragma once

#include"Accio.h"
#include"WorldState.h"
#include<ostream>

using namespace std;

namespace goap {
	struct Node {
		static int lastId;//static perque ens permet assignar ids unics i incrementals

		WorldState ws;//el estat del mon en aqet node
		int id;
		int parentId;//id del node pare daquest
		int g;//cost acumulat
		int h;//cost estimat
		const Action* action;//accio que permet entrar al stateWorlddel node actual

		Node();
		Node(const WorldState state, int _g, int _h, int _parenId, const Action* _action);

		int totalCost() const { return g + h; }

		//bool operator<(const Node& other);//mantindre els nodes ordenats

		friend ostream& operator<<(ostream& out, const Node& n);
	};

	bool operator<(const Node& left, const Node& right);

	inline ostream& operator<<(ostream& out, const Node& n) {
		out << "Node { id:" << n.id << " parent:" << n.parentId << " TotalCost:" << n.totalCost() << " G:" << n.g << " H:" << n.h;
		out << ", " << n.ws << "}";
		return out;
	}
}

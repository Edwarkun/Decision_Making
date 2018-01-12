#include "AlgoritmeEstrella.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;
goap::Planificador::Planificador(){}

int goap::Planificador::Heuristica(const WorldState& now, const WorldState& goal)const {
	return now.distanceTo(goal);
}

void goap::Planificador::addToOpenList(Node&& n) {
	//insert mantentin sort order
	auto it = lower_bound(begin(open), end(open), n);
	open.emplace(it, move(n));
}

goap::Node& goap::Planificador::popAndClose() {
	assert(!open.empty());
	closed.push_back(move(open.front()));
	open.erase(open.begin());

	return closed.back();
}

bool goap::Planificador::pertanyTancada(const WorldState& ws) const {
	if (find_if(begin(closed), end(closed), [&](const Node & n)
	{return n.ws == ws; }) == end(closed)) {
		return false;
	}
	return true;
}

vector<goap::Node>::iterator goap::Planificador::pertanyOberta(const WorldState& ws) {
	return find_if(begin(open), end(open), [&](const Node & n) {return n.ws == ws; });
}

void goap::Planificador::printLlistaOberta()const {
	for (const auto& i : open) {
		cout << i << endl;
	}
}

void goap::Planificador::printLlistaTancada()const {
	for (const auto& i : closed) {
		cout << i << endl;
	}
}

vector<goap::Action>goap::Planificador::plan(const WorldState& start, const WorldState& goal, const vector<Action>&actions) {
	if (start.meetsGoal(goal)) {
		return vector<goap::Action>();//si el node estat inicial i final son el mateix
	}

	open.clear();
	closed.clear();

	Node startingNode(start, 0, Heuristica(start, goal), 0, nullptr);

	open.push_back(move(startingNode));

	while (open.size() > 0) {
		Node& current(popAndClose());//busca un node amb el menor cost

		if (current.ws.meetsGoal(goal)) {
			vector<Action> thePlan;
			do {
				thePlan.push_back(*current.action);
				auto itr = find_if(begin(open), end(open), [&](const Node & n) { return n.id == current.parentId; });
				if (itr == end(open)) {
					itr = find_if(begin(closed), end(closed), [&](const Node & n) { return n.id == current.parentId; });
				}
				current = *itr;
			} while (current.parentId != 0);
			return thePlan;

		}//tanca lif

		//on podem anar desde aqui
		for (const auto& i : actions) {
			if (i.operableOn(current.ws)) {
				WorldState nextWS = i.actOn(current.ws);

				//skip si ja esta tancada
				if (pertanyTancada(nextWS)) {
					continue;
				}

				//mira un node amb el WS en la llsita oberta
				auto p_nextWS = pertanyOberta(nextWS);
				if (p_nextWS == end(open)) {//no es membre de la llista obert
					//fes un nou node, amb current com pare, recordint g i h
					Node found(nextWS, current.g + i.getCost(), Heuristica(nextWS, goal), current.id, &i);
					//add a la llista oberta
					addToOpenList(move(found));
				}
				else {//si YA es un membre de la llista oberta
				 //comprava si el current.g es millor que el guardat
					if (current.g + i.getCost() < p_nextWS->g) {
						p_nextWS->parentId = current.id;//fer current el pare
						p_nextWS->g = current.g + i.getCost();//recalculem cost
						p_nextWS->h = Heuristica(nextWS, goal);
						p_nextWS->action = &i;

						sort(begin(open), end(open));
					}
				}
			}
		}
	}//tanco el while

	throw runtime_error("A* no ha trobat cami possible");

}
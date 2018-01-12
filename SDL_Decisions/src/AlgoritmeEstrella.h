#pragma once

#include "Accio.h"
#include "NodeGOAP.h"
#include "WorldState.h"
#include <unordered_map>
#include <vector>
#include <ostream>

using namespace std;
namespace goap {
	class Planificador{
	private:
		vector<NodeGOAP> open;//A* llista oberta
		vector<NodeGOAP> closed;//A* llista tancada
		
		bool pertanyTancada(const WorldState& ws) const;//comprova si el worldState donat el conte algun node de la llista
		vector<goap::NodeGOAP>::iterator pertanyOberta(const WorldState& ws);

		NodeGOAP& popAndClose();//agafa el 1r node de open i la pasa a closed,retorna una refernciaaques node de close
		void addToOpenList(NodeGOAP&&);//mou un node donat (a rvalue reference)) dintre la llista oberta

		int Heuristica(const WorldState& now, const WorldState& goal)const;

	public:
		Planificador();

		void printLlistaOberta() const;
		void printLlistaTancada() const;

		//algoritme
		vector<Action>plan(const WorldState& start, const WorldState& goal, const vector<Action>& actions);


	};
}
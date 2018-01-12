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
		vector<Node> open;//A* llista oberta
		vector<Node> closed;//A* llista tancada
		
		bool pertanyTancada(const WorldState& ws) const;//comprova si el worldState donat el conte algun node de la llista
		vector<goap::Node>::iterator pertanyOberta(const WorldState& ws);

		Node& popAndClose();//agafa el 1r node de open i la pasa a closed,retorna una refernciaaques node de close
		void addToOpenList(Node&&);//mou un node donat (a rvalue reference)) dintre la llista oberta

		int Heuristica(const WorldState& now, const WorldState& goal)const;

	public:
		Planificador();

		void printLlistaOberta() const;
		void printLlistaTancada() const;

		//algoritme
		vector<Action>plan(const WorldState& start, const WorldState& goal, const vector<Action>& actions);


	};
}
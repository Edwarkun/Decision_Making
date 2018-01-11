#pragma once
#include <string>
#include <unordered_map>

using namespace std;

namespace goap {
	struct WorldState;
	class Action
	{
	private:
		string name;//nom de la accio
		int cost;//cost de la accio

		//precondicions en un map, pot tindre varies sense importar ordre
		unordered_map<int, bool> preconditions;

		//efectes en un map, pot tindre varis sense importar ordre
		unordered_map<int, bool> effects;
	public:
		Action();
		Action(string _name, int _cost);


		bool operableOn(const goap::WorldState& ws) const;//funcio que comprova si la accio es permesa en el actual estat del mon
													//ws es el estat del mon actual en questio
													//retornara true si el Ws compleix les precondicions

		WorldState actOn(const WorldState& ws) const;//actua en el WS actual, retorna una COPIA del worldState amb els efectesaplicats

		void setPrecondition(const int key, const bool value);//key = nom de la precondicio, value=valorque ha de tindre
		void setEffect(const int key, const bool value);


		int getCost() const { return cost; }
		string getNom() const { return name; }

	};

}
//~Action();
#pragma once
#include<ostream>
#include<string>
#include<map>

using namespace std;

namespace goap {
	struct WorldState
	{
		float priority;//util per si es un estat objectiu, distingirlo daltres posibles objectius
		string name;
		map<int, bool> variablesMon;//conjunt de totes les varibalesEstat que desciru el estat del el nostre mon

		WorldState(const string name = "");


		void setVariablesMon(const int varId, const bool value);//exemple:agentViu/true
		bool getVariablesMon(const int varId)const;

		bool meetsGoal(const WorldState& goalState)const;//util si es un estatObjectiu, l'estat "altre" coneix els requeriments daquest objectius?
														//pren en comtpe els states varaibls del objectiu, y quins son importants per arribar
		
		int distanceTo(const WorldState& goalState) const;//nombre de variables del worldStaet han decanviar del actual al goal

		bool operator==(const WorldState& other) const;//operador digualtat retorna true si son iguals

		friend ostream& operator<<(ostream& out, const WorldState& n);
	
	};

	//imprimeix tote les variables de worldState
	inline ostream& operator<<(ostream& out, const WorldState& n) {
		out << "WorldState { ";
		for (const auto& i : n.variablesMon) {
			out << i.second << " ";
		}
		out << "}";
		return out;
	}
}
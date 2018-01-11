#include<iostream>
#include"Accio.h"
#include"WorldState.h"
//tambe shauria dincloure el .h amb lalgoritme, aqui el node no, ya que sinclou en la del algoritme tmb
#include<vector>
#include <map>
using namespace goap;
using namespace std;
/*void main() {
	cout<< "PUTAS HARRY PUUUUUUUUUUUUTAS...\n";
	vector<Action>actions;

	//escribim els estats del mon
	const int AgentViu = 1;
	const int AgentTeArma = 2;
	const int ArmaCarregada = 3;
	
	//definim les accions, ve lo pepino
	Action explorar("ExplorarEnemics", 5);
	explorar.setPrecondition(AgentViu, false);
	explorar.setEffect(AgentViu, true);
	actions.push_back(explorar);


	Action carregar("CarregarArma", 5);
	carregar.setPrecondition(AgentTeArma, true);
	carregar.setPrecondition(AgentViu, true);
	carregar.setEffect(ArmaCarregada, true);
	actions.push_back(carregar);

	Action pepe("pepeEsMajo", 5);
	pepe.setPrecondition(AgentTeArma, false);
	pepe.setEffect(AgentViu, false);
	actions.push_back(pepe);

	//estat inicial
	WorldState estatInicial;
	estatInicial.setVariablesMon(AgentViu, false);
	estatInicial.setVariablesMon(AgentTeArma, true);
	estatInicial.setVariablesMon(ArmaCarregada, false);

	//estat final
	WorldState estatObjectiu;
	estatObjectiu.setVariablesMon(AgentViu, true);
	estatObjectiu.setVariablesMon(AgentTeArma, true);
	estatObjectiu.setVariablesMon(ArmaCarregada, true);
	estatObjectiu.priority = 50;

	for (auto it = 0; it < actions.size; it++) {
		it = 
	}

}*/

int main() {
	std::vector<int> myvector(10);
	bool a = false;
	try {
		if(a == false)myvector.at(10);      // vector::at throws an out-of-range
	}
	catch (const out_of_range&) {
	cout << "Out of Range error: " << '\n';
	}
	return 0;
}
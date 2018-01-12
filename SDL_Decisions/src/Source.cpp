#include<iostream>
#include"Accio.h"
#include"WorldState.h"
#include"AlgoritmeEstrella.h"
//tambe shauria dincloure el .h amb lalgoritme, aqui el node no, ya que sinclou en la del algoritme tmb
#include<vector>

using namespace goap;
using namespace std;

int main(void) {
	cout<< "GOAP...\n";
	vector<Action>actions;

	//escribim els estats del mon
	const int AgentViu = 5;
	const int AgentTeArma = 10;
	const int ArmaCarregada = 15;
	const int AgentTeBomba = 20;
	const int EnemicVisible = 25;
	const int EnemicAlineat = 30;
	const int EnemicViu = 35;
	const int EnemicAprop = 40;
	
	//definim les accions, ve lo pepino
	Action explorar("ExplorarEnemics", 5);
	explorar.setPrecondition(AgentViu, true);
	explorar.setPrecondition(EnemicViu, true);
	explorar.setPrecondition(EnemicVisible, false);
	explorar.setEffect(EnemicVisible, true);
	actions.push_back(explorar);

	Action aproparse("AproparseToEnemic", 5);
	aproparse.setPrecondition(EnemicViu, true);
	aproparse.setPrecondition(EnemicVisible, true);
	aproparse.setPrecondition(EnemicAprop, false);
	aproparse.setEffect(EnemicAprop, true);
	actions.push_back(aproparse);

	Action apuntar("Apuntar", 5);
	apuntar.setPrecondition(EnemicViu, true);
	apuntar.setPrecondition(EnemicAprop, true);
	apuntar.setPrecondition(AgentTeArma, true);
	apuntar.setPrecondition(EnemicAlineat, false);
	apuntar.setEffect(EnemicAlineat, true);
	actions.push_back(apuntar);

	Action disparar("Disparar", 5);;
	disparar.setPrecondition(EnemicViu, true);
	disparar.setPrecondition(ArmaCarregada, true);
	disparar.setEffect(EnemicViu, false);
	actions.push_back(disparar);

	Action carregar("CarregarArma", 5);
	carregar.setPrecondition(AgentTeArma, true);
	carregar.setPrecondition(AgentViu, true);
	carregar.setPrecondition(ArmaCarregada, false);
	carregar.setEffect(ArmaCarregada, true);
	actions.push_back(carregar);

	Action detonar("DetonarBomba", 5);
	detonar.setPrecondition(AgentViu, true);
	detonar.setPrecondition(AgentTeArma, false);
	detonar.setPrecondition(AgentTeBomba, true);
	detonar.setPrecondition(EnemicViu, true);
	detonar.setPrecondition(EnemicAprop, true);
	detonar.setEffect(AgentTeBomba, false);
	detonar.setEffect(EnemicViu, false);
	actions.push_back(detonar);

	Action fugir("FugirDeEnemic", 6);
	fugir.setPrecondition(AgentViu, true);
	fugir.setPrecondition(EnemicViu, true);
	fugir.setPrecondition(AgentTeArma, false);
	fugir.setPrecondition(AgentTeBomba, false);
	fugir.setPrecondition(EnemicAprop, true);
	fugir.setEffect(EnemicAprop, false);
	actions.push_back(fugir);


	//estat inicial
	WorldState estatInicial;
	estatInicial.setVariablesMon(AgentViu, true);
	estatInicial.setVariablesMon(AgentTeArma, true);
	estatInicial.setVariablesMon(ArmaCarregada, false);
	estatInicial.setVariablesMon(AgentTeBomba, false);
	estatInicial.setVariablesMon(EnemicVisible, false);
	estatInicial.setVariablesMon(EnemicAlineat, false);
	estatInicial.setVariablesMon(EnemicViu, true);
	estatInicial.setVariablesMon(EnemicAprop, false);

	//estat final
	WorldState estatObjectiu;
	estatObjectiu.setVariablesMon(AgentViu, true);
	estatObjectiu.setVariablesMon(AgentTeArma, true);
	estatObjectiu.setVariablesMon(ArmaCarregada, false);
	estatObjectiu.setVariablesMon(AgentTeBomba, false);
	estatObjectiu.setVariablesMon(EnemicVisible, true);
	estatObjectiu.setVariablesMon(EnemicAlineat, true);
	estatObjectiu.setVariablesMon(EnemicAprop, true);
	estatObjectiu.setVariablesMon(EnemicViu, false);
	estatObjectiu.priority = 200;


	Planificador A;
	try {
		vector<Action> thePlan = A.plan(estatInicial, estatObjectiu, actions);
		cout << "Cami trobat\n";
		for (vector<Action>::reverse_iterator rIt = thePlan.rbegin(); rIt != thePlan.rend(); ++rIt) {
			cout << rIt->getNom() << endl;
		}
	}
	catch (const exception&) {
		cout << "No, no sha torbat cami\n";
	}

}
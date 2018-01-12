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
	const int AgentViu = 1;
	const int AgentTeArma = 2;
	const int ArmaCarregada = 3;
	const int AgentTeBomba = 4;
	const int EnemicVisible = 5;
	const int EnemicAlineat = 6;
	const int EnemicViu = 7;
	const int EnemicAprop = 8;
	
	//accions
	Action explorar("ExplorarEnemics",100);
	explorar.setPrecondition(AgentViu, true);
	explorar.setPrecondition(EnemicViu, true);
	explorar.setPrecondition(EnemicVisible, false);
	explorar.setEffect(EnemicVisible, true);
	actions.push_back(explorar);

	Action aproparse("AproparseToEnemic", 150);
	aproparse.setPrecondition(EnemicViu, true);
	aproparse.setPrecondition(EnemicVisible, true);
	aproparse.setPrecondition(EnemicAprop, false);
	aproparse.setEffect(EnemicAprop, true);
	actions.push_back(aproparse);

	Action apuntar("Apuntar", 20);
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

	Action carregar("CarregarArma", 30);
	carregar.setPrecondition(AgentTeArma, true);
	carregar.setPrecondition(AgentViu, true);
	carregar.setPrecondition(ArmaCarregada, false);
	carregar.setEffect(ArmaCarregada, true);
	actions.push_back(carregar);

	Action detonar("DetonarBomba", 100);
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
	/*estatObjectiu.setVariablesMon(AgentViu, true);
	estatObjectiu.setVariablesMon(AgentTeArma, true);
	estatObjectiu.setVariablesMon(ArmaCarregada, false);
	estatObjectiu.setVariablesMon(AgentTeBomba, false);
	estatObjectiu.setVariablesMon(EnemicVisible, true);
	estatObjectiu.setVariablesMon(EnemicAlineat, true);
	estatObjectiu.setVariablesMon(EnemicAprop, true);*/
	estatObjectiu.setVariablesMon(EnemicViu, false);
	estatObjectiu.setVariablesMon(EnemicAlineat, true);
	estatObjectiu.priority = 50;


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
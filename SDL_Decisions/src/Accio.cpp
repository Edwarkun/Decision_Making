#include "Accio.h"
#include "WorldState.h"

goap::Action::Action() : cost(0) {
}

goap::Action::Action(string _name, int _cost) : Action(){
	//èrque els constructor delegats no poden incialitzarse  & delegar al mateix temps
	name = _name;
	cost = _cost;
}

bool goap::Action::operableOn(const WorldState& ws) const {
	for (const auto& i : preconditions) {//iterador del tipus Const Action& que recorre les preconditions
		/*try {
			if (ws.variablesMon.at(i.first) != i.second) {//si la key(ex.agentViu)de la precondicio !ESTROBA! en l'estat del mon actual
				//el seu valor bool(true/false) no concorda amb el de la preocnidicio siginfica que no podrem realitzarla perque no es compleix
				return false;//per tant no opera en aquest worldState
			}
		}//tots els try requereix un controlador:catch
		catch (const out_of_range&) {
			return false;
		}*/
		if (ws.variablesMon.at(i.first) != i.second) {//si la key(ex.agentViu)de la precondicio !ESTROBA! en l'estat del mon actual
													  //el seu valor bool(true/false) no concorda amb el de la preocnidicio siginfica que no podrem realitzarla perque no es compleix
			return false;//per tant no opera en aquest worldState
		}
	}
	return true;
}

goap::WorldState goap::Action::actOn(const WorldState& ws) const {
	goap::WorldState tmp(ws);//guardes el ActualState en un temporañ
	for (const auto& i : effects) {//iterador del tipus effects(map)
		tmp.setVariablesMon(i.first, i.second);//assignes el estat amb el nou valor(t/f)
	}
	return tmp;//retornes la copia que ara es el actual World STate
}

void goap::Action::setPrecondition(const int key, const bool value) {
	preconditions[key] = value;
}

void goap::Action::setEffect(const int key, const bool value) {
	effects[key] = value;
}
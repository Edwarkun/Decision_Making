#include "SceneGOAP.h"

SceneGOAP::SceneGOAP() {
	srand(time(NULL));
	agent_alive = true;
	agent_has_weapon = rand() % 2;
	agent_loaded = rand() % 2;
	agent_has_bomb = rand() % 2;
	enemy_visible = rand() % 2;
	enemy_aligned = rand() % 2;
	enemy_close = rand() % 2;
	enemy_alive = true;

	running = false;
	changingState = false;
	goalReached = false;

	previousAction = new Text("Start", Vector2D(TheApp::Instance()->getWinSize().x / 2, 100), TheApp::Instance()->getRenderer(), 40, true);
	previousAction->SetTextColor(150, 150, 150);
	actualAction = new Text("Press Space to start", Vector2D(TheApp::Instance()->getWinSize().x / 2, TheApp::Instance()->getWinSize().y / 2), TheApp::Instance()->getRenderer(), 50, true);
	actualAction->SetTextColor(200, 200, 200);
	nextAction = new Text("-----------", Vector2D(TheApp::Instance()->getWinSize().x / 2, TheApp::Instance()->getWinSize().y - 100), TheApp::Instance()->getRenderer(), 40, true);
	nextAction->SetTextColor(150, 150, 150);
	int a = -50;

	Text* info = new Text("World data", Vector2D(200, a + 140), TheApp::Instance()->getRenderer(), 30, true);
	agentDataText.push_back(info);

	Text* agent_alive_text = new Text(agent_alive ? "Agent alive: true" : "Agent alive: false", Vector2D(100, a + 200), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(agent_alive_text);
	
	Text* agent_armed_text = new Text(agent_has_weapon ? "Agent armed: true" : "Agent armed: false", Vector2D(100, a + 260), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(agent_armed_text);

	Text* agent_loaded_text = new Text(agent_loaded ? "Weapon Loaded: true" : "Weapon Loaded: false", Vector2D(100, a + 320), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(agent_loaded_text);

	Text* agent_has_bomb_text = new Text(agent_has_bomb ? "Agent has bomb: true" : "Agent has bomb:  false", Vector2D(100, a + 380), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(agent_has_bomb_text);

	Text* enemy_visible_text = new Text(enemy_visible ? "Enemy visible: true" : "Enemy visible: false", Vector2D(100, a + 440), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(enemy_visible_text);

	Text* enemy_aligned_text = new Text(enemy_aligned ? "Enemy aligned: true" : "Enemy aligned: false", Vector2D(100, a + 500), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(enemy_aligned_text);

	Text* enemy_close_text = new Text(enemy_close ? "Enemy close: true" : "Enemy close: false", Vector2D(100, a + 560), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(enemy_close_text);

	Text* enemy_alive_text = new Text(enemy_alive ? "Enemy alive: true" : "Enemy alive: false", Vector2D(100, a + 620), TheApp::Instance()->getRenderer(), 20, false);
	agentDataText.push_back(enemy_alive_text);

	//Execute the GOAP algorythm and extract the data
	ExecuteGOAP();
}
SceneGOAP::~SceneGOAP() {
	delete actualAction;
	delete nextAction;
	delete previousAction;
	for (int i = 0; i < agentDataText.size(); i++) {
		delete agentDataText[i];
	}
}
void SceneGOAP::update(float delta, SDL_Event *event) {
	float dtime = delta;
	if (dtime > 60.f / 1000.f) {
		dtime = 60.f / 1000.f;
	}
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE && running == false) {
			running = true;
			actualIndex = 0;
			//text startup
			if (actualIndex < actionNames.size()) {
				previousAction->SetText("Start");
				actualAction->SetText(actionNames[actualIndex]);
				if (actionNames.size() > 1) {
					nextAction->SetText(actionNames[actualIndex + 1]);
				}
				actualIndex++;
			}
			else {
				previousAction->SetText("No path found");
				actualAction->SetText("Finished");
				nextAction->SetText("Press 2 to reset");
			}
		}
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		break;
	default:
		break;
	}
	if (running && !goalReached) {
		if (changingState) {
			transitionTimer += delta;
			if (transitionTimer > 0.75f) {
				timer -= delta * 1.25f * 4.f;
			}
			if (transitionTimer > 1.f) {
				transitionTimer = 0.f;
				timer = 0.f;
				changingState = false;
				//Execute state swap here
				swapActions();
			}
		}
		else {
			timer += delta;
			if (timer >= 1.25f) {
				timer = 1.25f;
				changingState = true;
			}
		}
	}
}
void SceneGOAP::draw() {
	if (running) {
		previousAction->RenderText();
		actualAction->RenderText();
		nextAction->RenderText();
		for (int i = 0; i < agentDataText.size(); i++) {
			agentDataText[i]->RenderText();
		}
		drawProgressBar();
	}
	else {
		actualAction->RenderText();
	}
}
const char* SceneGOAP::getTitle()
{
	return "Ayy please work";
}
void SceneGOAP::drawProgressBar() {
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	//Top bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40,
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40);
	//Down Bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f + 120,
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f + 120);
	//Right Bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f + 120,
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40);
	//Left Bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f + 120,
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40);
	SDL_Rect fillbar;
	fillbar.x = TheApp::Instance()->getWinSize().x / 2.f + 200;
	fillbar.y = TheApp::Instance()->getWinSize().y / 2.f + 40;
	fillbar.w = ((TheApp::Instance()->getWinSize().x - 50) - (TheApp::Instance()->getWinSize().x / 2.f + 200)) * timer / 1.25f;
	fillbar.h = 80;
	SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &fillbar);
}
void SceneGOAP::swapActions() {
	if (actualIndex == actionNames.size()) {
		goalReached = true;
		nextAction->SetText("Press 2 to reset");
		previousAction->SetText("Finished!");
	}
	if (actualIndex < actionNames.size()) {
		previousAction->SetText(actualAction->GetText());
		actualAction->SetText(actionNames[actualIndex]);
		if (actualIndex < actionNames.size() - 1) {
			nextAction->SetText(actionNames[actualIndex + 1]);
		}
		else {
			nextAction->SetText(" --- ");
		}
		actualIndex++;
	}
}
void SceneGOAP::ExecuteGOAP() {
	cout << "GOAP...\n";
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
	Action explorar("ExplorarEnemics", 100);
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
	estatInicial.setVariablesMon(AgentViu, agent_alive);
	estatInicial.setVariablesMon(AgentTeArma, agent_has_weapon);
	estatInicial.setVariablesMon(ArmaCarregada, agent_loaded);
	estatInicial.setVariablesMon(AgentTeBomba, agent_has_bomb);
	estatInicial.setVariablesMon(EnemicVisible, enemy_visible);
	estatInicial.setVariablesMon(EnemicAlineat, enemy_aligned);
	estatInicial.setVariablesMon(EnemicViu, enemy_alive);
	estatInicial.setVariablesMon(EnemicAprop, enemy_close);

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
		cout << "Cami trobat" << std::endl;
		for (vector<Action>::reverse_iterator rIt = thePlan.rbegin(); rIt != thePlan.rend(); ++rIt) {
			actionNames.push_back(rIt->getNom());
			cout << rIt->getNom() << std::endl;
		}
	}
	catch (const exception&) {
		cout << "No, no sha torbat cami\n";
	}

}
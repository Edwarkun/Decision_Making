#include "SceneGOAP.h"

SceneGOAP::SceneGOAP() {
	srand(time(NULL));
	agent_alive = rand() % 2;
	agent_has_weapon = rand() % 2;
	agent_loaded = rand() % 2;
	agent_has_bomb = rand() % 2;
	enemy_visible = rand() % 2;
	enemy_aligned = rand() % 2;
	enemy_close = rand() % 2;
	enemy_alive =  rand() % 2;

	running = false;
	changingState = false;
	goalReached = false;

	previousAction = new Text("Start", Vector2D(TheApp::Instance()->getWinSize().x / 2, 100), TheApp::Instance()->getRenderer(), 60, true);
	previousAction->SetTextColor(150, 150, 150);
	actualAction = new Text("Press Space to start", Vector2D(TheApp::Instance()->getWinSize().x / 2, TheApp::Instance()->getWinSize().y / 2), TheApp::Instance()->getRenderer(), 80, true);
	actualAction->SetTextColor(200, 200, 200);
	nextAction = new Text("-----------", Vector2D(TheApp::Instance()->getWinSize().x / 2, TheApp::Instance()->getWinSize().y - 100), TheApp::Instance()->getRenderer(), 60, true);
	nextAction->SetTextColor(150, 150, 150);
	int a = -50;
	Text* agent_alive_text = new Text(agent_alive ? "Agent alive: true" : "Agent alive: false", Vector2D(100, a + 200), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(agent_alive_text);
	
	Text* agent_armed_text = new Text(agent_has_weapon ? "Agent armed: true" : "Agent armed: false", Vector2D(100, a + 260), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(agent_armed_text);

	Text* agent_loaded_text = new Text(agent_loaded ? "Weapon Loaded: true" : "Weapon Loaded: false", Vector2D(100, a + 320), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(agent_loaded_text);

	Text* agent_has_bomb_text = new Text(agent_has_bomb ? "Agent has bomb: true" : "Agent has bomb:  false", Vector2D(100, a + 380), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(agent_has_bomb_text);

	Text* enemy_visible_text = new Text(enemy_visible ? "Enemy visible: true" : "Enemy visible: false", Vector2D(100, a + 440), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(enemy_visible_text);

	Text* enemy_aligned_text = new Text(enemy_aligned ? "Enemy aligned: true" : "Enemy aligned: false", Vector2D(100, a + 500), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(enemy_aligned_text);

	Text* enemy_close_text = new Text(enemy_close ? "Enemy close: true" : "Enemy close: false", Vector2D(100, a + 560), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(enemy_close_text);

	Text* enemy_alive_text = new Text(enemy_alive ? "Enemy alive: true" : "Enemy alive: false", Vector2D(100, a + 620), TheApp::Instance()->getRenderer(), 30, false);
	agentDataText.push_back(enemy_alive_text);

	//Execute the GOAP algorythm and extract the data
	actions.push_back("Action 1");
	actions.push_back("Action 2");
	actions.push_back("Action 3");
	actions.push_back("Action 4");
	actions.push_back("Action 5");
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
			if (actualIndex < actions.size()) {
				previousAction->SetText("Start");
				actualAction->SetText(actions[actualIndex]);
				if (actions.size() > 1) {
					nextAction->SetText(actions[actualIndex + 1]);
				}
				actualIndex++;
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
		(TheApp::Instance()->getWinSize().y) / 2.f - 40,
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f - 40);
	//Down Bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40,
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40);
	//Right Bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40,
		(TheApp::Instance()->getWinSize().x) - 50,
		(TheApp::Instance()->getWinSize().y) / 2.f - 40);
	//Left Bar
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(),
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f + 40,
		(TheApp::Instance()->getWinSize().x) / 2.f + 200,
		(TheApp::Instance()->getWinSize().y) / 2.f - 40);
	SDL_Rect fillbar;
	fillbar.x = TheApp::Instance()->getWinSize().x / 2.f + 200;
	fillbar.y = TheApp::Instance()->getWinSize().y / 2.f - 40;
	fillbar.w = ((TheApp::Instance()->getWinSize().x - 50) - (TheApp::Instance()->getWinSize().x / 2.f + 200)) * timer / 1.25f;
	fillbar.h = 80;
	SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &fillbar);
}
void SceneGOAP::swapActions() {
	if (actualIndex == actions.size()) {
		goalReached = true;
		nextAction->SetText("Press 2 to reset");
		previousAction->SetText("Finished!");
	}
	if (actualIndex < actions.size()) {
		previousAction->SetText(actualAction->GetText());
		actualAction->SetText(actions[actualIndex]);
		if (actualIndex < actions.size() - 1) {
			nextAction->SetText(actions[actualIndex + 1]);
		}
		else {
			nextAction->SetText(" --- ");
		}
		actualIndex++;
	}
}
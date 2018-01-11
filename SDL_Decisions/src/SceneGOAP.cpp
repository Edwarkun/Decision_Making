#include "SceneGOAP.h"

SceneGOAP::SceneGOAP() {
	agent_alive = true;
	agent_has_weapon = true;
	agent_loaded = true;
	agent_has_bomb = true;
	enemy_visible = true;
	enemy_aligned = true;
	enemy_close = true;
	enemy_alive = true;
	running = false;
	previousAction = new Text("Previous Action", Vector2D(TheApp::Instance()->getWinSize().x / 2, 100), TheApp::Instance()->getRenderer(), 80, true);
	previousAction = new Text("Actual Action", Vector2D(TheApp::Instance()->getWinSize().x / 2, 100), TheApp::Instance()->getRenderer(), 80, true);
	previousAction = new Text("Next Action", Vector2D(TheApp::Instance()->getWinSize().x / 2, 100), TheApp::Instance()->getRenderer(), 80, true);
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
			/*if (!actions.empty()) {
				previousAction->SetText("Start");
				actualAction->SetText(actions[actualIndex]);
				if (actions.size() > 1) {
					nextAction->SetText(actions[actualIndex + 1]);
				}
			}*/
		}
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		break;
	default:
		break;
	}
	if (running) {

	}
}
void SceneGOAP::draw() {
	if (running) {
		previousAction->RenderText();
		actualAction->RenderText();
		nextAction->RenderText();
	}
}
const char* SceneGOAP::getTitle()
{
	return "Ayy please work";
}
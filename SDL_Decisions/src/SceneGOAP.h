#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Text.h"
#include "time.h"
#include "SDL_SimpleApp.h"

class SceneGOAP : public Scene {
public:
	SceneGOAP();
	~SceneGOAP();
	void update(float dtime, SDL_Event *event);
	void draw();
	void drawProgressBar();
	void swapActions();
	const char* getTitle();
	//Agent variables
	bool agent_alive;
	bool agent_has_weapon;
	bool agent_loaded;
	bool agent_has_bomb;
	bool enemy_visible;
	bool enemy_aligned;
	bool enemy_close;
	bool enemy_alive;
	bool running;
	bool goalReached;
	//Visual variables
	float timer;
	float transitionTimer;
	bool changingState;
	int actualIndex;
	std::vector<std::string> actions;
	std::vector<Text*> agentDataText;
	Text* previousAction;
	Text* actualAction;
	Text* nextAction;
};
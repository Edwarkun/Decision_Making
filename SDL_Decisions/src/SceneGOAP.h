#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Text.h"
#include "time.h"
#include "SDL_SimpleApp.h"
#include<iostream>
#include"Accio.h"
#include"WorldState.h"
#include"AlgoritmeEstrella.h"
//tambe shauria dincloure el .h amb lalgoritme, aqui el node no, ya que sinclou en la del algoritme tmb
#include<vector>

using namespace goap;
using namespace std;

class SceneGOAP : public Scene {
public:
	SceneGOAP();
	~SceneGOAP();
	void update(float dtime, SDL_Event *event);
	void draw();
	void drawProgressBar();
	void swapActions();
	void ExecuteGOAP();
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
	std::vector<std::string> actionNames;
	std::vector<Text*> agentDataText;
	Text* previousAction;
	Text* actualAction;
	Text* nextAction;
};
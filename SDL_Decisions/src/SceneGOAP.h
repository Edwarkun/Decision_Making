#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Text.h"
#include "SDL_SimpleApp.h"

class SceneGOAP : public Scene {
public:
	SceneGOAP();
	~SceneGOAP();
	void update(float dtime, SDL_Event *event);
	void draw();
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
	//Visual variables
	float timer;
	int actualIndex;
	std::vector<std::string> actions;
	Text* previousAction;
	Text* actualAction;
	Text* nextAction;
	SDL_Rect* outerRect;
	SDL_Rect* fillBar;
};
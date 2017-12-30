#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Node.h"
#include "Text.h"

class ScenePlanning :
	public Scene
{
public:
	ScenePlanning();
	~ScenePlanning();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	void initMaze();
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector< std::vector<int> > terrain;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);

	void CreateGrid(const std::vector<std::vector<int>>&);

	std::vector<Node*> grid;
	Text* thirst;
	Text* coins;
	Text* tired;
	Text* totalCoins;
	Text* agentState;

	Path mine_home, mine_saloon, mine_bank;
	Path home_mine, home_saloon, home_bank;
	Path saloon_home, saloon_mine, saloon_bank;
	Path bank_home, bank_mine, bank_saloon;

};

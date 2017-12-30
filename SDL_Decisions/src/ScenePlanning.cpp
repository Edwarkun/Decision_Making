#include "ScenePlanning.h"

using namespace std;

ScenePlanning::ScenePlanning()
{
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->SetGrid(grid);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);


	// set agent position coords to the center of a random cell
	agents[0]->setPosition(cell2pix(Vector2D(35, 20)));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = agents[0]->getTarget();
	
	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;

	thirst = new Text("Thist: " + std::to_string(agents[0]->thirst).substr(0, 5), Vector2D(48, 16 + 32 * 7), TheApp::Instance()->getRenderer(), 20, false);
	coins = new Text("Coins: " + std::to_string(agents[0]->coins) + "/" + std::to_string(agents[0]->max_coins), Vector2D(48, 16 + 32 * 8), TheApp::Instance()->getRenderer(), 20, false);
	totalCoins = new Text("Coins in bank: " + std::to_string(agents[0]->total_coins), Vector2D(48, 16 + 32 * 9), TheApp::Instance()->getRenderer(), 20, false);
	tired = new Text("Tiredness: " + std::to_string(agents[0]->tiredness).substr(0, 5), Vector2D(48, 16 + 32 * 10), TheApp::Instance()->getRenderer(), 20, false);
	agentState = new Text(agents[0]->stateNotification, Vector2D(30, 30), TheApp::Instance()->getRenderer(), 20, false);
		//Text test("Heading to the Mine", Vector2D(30, 30), TheApp::Instance()->getRenderer(), 20, false);		
}

ScenePlanning::~ScenePlanning()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete thirst;
	delete coins;
	delete tired;
	delete totalCoins;
	delete agentState;
}

void ScenePlanning::update(float dtime, SDL_Event *event)
{
	if (dtime > 60.f / 1000.f) {
		dtime = 60.f / 1000.f;
	}
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		/*if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (isValidCell(cell))
			{
				agents[0]->setTarget(cell2pix(cell));
				path = agents[0]->FindPath(grid, cell2pix(pix2cell(agents[0]->getPosition())), agents[0]->getTarget());
			}
		}*/
		break;
	default:
		break;
	}
	if ((currentTargetIndex == -1) && (path.points.size()>0))
		currentTargetIndex = 0;

	if (currentTargetIndex >= 0)
	{	
		float dist = Vector2D::Distance(agents[0]->getPosition(), path.points[currentTargetIndex]);
		if (dist < path.ARRIVAL_DISTANCE)
		{
			if (currentTargetIndex == path.points.size() - 1)
			{
				if (dist < 3)
				{
					path.points.clear();
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0,0));
					// if we have arrived to the coin, replace it ina random cell!
					if (pix2cell(agents[0]->getPosition()) == coinPosition)
					{
						coinPosition = Vector2D(-1, -1);
						while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition()))<3))
							coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
					}
				}
				else
				{
					Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], currentTarget, path.ARRIVAL_DISTANCE, dtime);
					agents[0]->update(steering_force, dtime, event);
				}
				return;
			}
			currentTargetIndex++;
		}

		currentTarget = path.points[currentTargetIndex];
		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		agents[0]->update(steering_force, dtime, event);
	} 
	else
	{
		agents[0]->update(Vector2D(0,0), dtime, event);
	}
	if (Vector2D(agents[0]->getPosition() - agents[0]->getTarget()).Length() > 32 && path.points.size() == 0) {
		path = agents[0]->FindPath(grid, cell2pix(pix2cell(agents[0]->getPosition())), agents[0]->getTarget());
		coinPosition = agents[0]->getTarget();
	}
	thirst->SetText("Thist: " + std::to_string(agents[0]->thirst).substr(0, 5));
	coins->SetText("Coins: " + std::to_string(agents[0]->coins) + "/" + std::to_string(agents[0]->max_coins));
	tired->SetText("Tiredness: " + std::to_string(agents[0]->tiredness).substr(0, 5));
	totalCoins->SetText("Coins in bank: " + std::to_string(agents[0]->total_coins));
	agentState->SetText(agents[0]->stateNotification);

	if (agents[0]->thirst > agents[0]->limit_thirst) {
		thirst->SetTextColor(255, 125, 125);
	}
	else {
		thirst->SetTextColor(255, 255, 255);
	}

	if (agents[0]->tiredness > agents[0]->limit_tiredness) {
		tired->SetTextColor(255, 125, 125);
	}
	else {
		tired->SetTextColor(255, 255, 255);
	}

	if (agents[0]->coins == agents[0]->max_coins) {
		coins->SetTextColor(255, 255, 125);
	}
	else {
		coins->SetTextColor(255, 255, 255);
	}
		
}

void ScenePlanning::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	thirst->RenderText();
	tired->RenderText();
	coins->RenderText();
	totalCoins->RenderText();
	agentState->RenderText();

	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* ScenePlanning::getTitle()
{
	return "SDL Steering Behaviors :: PathFinding1 Demo";
}

void ScenePlanning::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
	}
}

void ScenePlanning::drawCoin()
{
	Vector2D coin_coords = agents[0]->GetGoldNuggetPosition();
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void ScenePlanning::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 192, 608, 32 };
	maze_rects.push_back(rect);
	rect = { 672, 192, 608, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);
	
	rect = { 0,32,32,736 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,736 };
	maze_rects.push_back(rect);

	rect = { 416,512,32,268 };
	maze_rects.push_back(rect);
	rect = { 832,512,32,268 };
	maze_rects.push_back(rect);
	
	rect = { 32,480,128,32 };
	maze_rects.push_back(rect);
	rect = { 288,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 704,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 1120,480,128,32 };
	maze_rects.push_back(rect);

	// Initialize the terrain matrix (for each cell a zero value indicates it's a wall)
	
	// (1st) initialize all cells to 1 by default
	for (int i = 0; i < num_cell_x; i++)
	{
		vector<int> terrain_col(num_cell_y, 1); 
		terrain.push_back(terrain_col);
	}
	// (2nd) set to zero all cells that belong to a wall
	int offset = CELL_SIZE / 2;
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			Vector2D cell_center ((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
			for (unsigned int b = 0; b < maze_rects.size(); b++)
			{
				if (Vector2DUtils::IsInsideRect(cell_center, (float)maze_rects[b].x, (float)maze_rects[b].y, (float)maze_rects[b].w, (float)maze_rects[b].h))
				{
					terrain[i][j] = 0;
				    break;
				}  
			}
			
		}
	}
	CreateGrid(terrain);
}

bool ScenePlanning::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D ScenePlanning::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D ScenePlanning::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x/CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool ScenePlanning::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()) )
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}

void ScenePlanning::CreateGrid(const std::vector<std::vector<int>>& maze) {
	int offset = CELL_SIZE / 2;
	bool* leftWall = new bool[maze[0].size()];

	std::queue<Node*> leftNodes;
	bool topWall = true;
	for (int i = 0; i < maze.size(); i++) { // Columns
		for (int j = 0; j < maze[i].size(); j++) { // Rows
			if (maze[i][j] == 0) { // that position is actually a wall, we won't create a node
				if (!leftWall[j]) {//we prevent diagonal linking
					leftNodes.pop();
				}
				topWall = true;
				leftWall[j] = true;
			}
			else {
				Node* newNode = new Node(Vector2D(offset + i * CELL_SIZE, offset + j * CELL_SIZE), maze[i][j]);

				if (leftWall[j]) { // if the left node was a wall we store the actual one it into a queue
					leftWall[j] = false;
					if (i != maze.size() - 1)
						leftNodes.push(newNode);
				}
				else { // if the left node wasn't a wall
					newNode->AddNB(leftNodes.front());
					leftNodes.front()->AddNB(newNode);
					leftNodes.pop();
					if (i != maze.size() - 1)
						leftNodes.push(newNode);
				}

				if (!topWall) {
					newNode->AddNB(grid.back());
					grid.back()->AddNB(newNode);
				}
				grid.push_back(newNode);
				topWall = false;
			}
		}
	}
	delete[] leftWall;
}
#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include "SteeringBehavior.h"

#include "Path.h"
#include "Node.h"
#include <unordered_map>
#include <queue>

//AI language initialisation
/*
#define BeginStateMachine	if(state < 0){ if (0) {
#define EndStateMachine		return (true);} } else { \
							return (false);} return (false);
#define State(a)			return (true); } } else if (a == state) {if(0){
#define OnEvent(a)			return (true); } else if (a == event) {
#define OnEnter				OnEvent(EVENT_Enter)
#define OnUpdate			OnEvent(EVENT_Update)
#define OnExit				OnEvent(EVENT_Exit)
*/
//We're going to use the function pointer style and not the macro style defined above

enum nextState { State_Saloon, State_Mine, State_Home, State_Bank };

class State;
class Agent
{
	friend class SteeringBehavior;
	friend class State;

private:

	SteeringBehavior *steering_behavior;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Color color;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	int coins;
	int max_coins;
	int total_coins;
	int drink_cost;
	float tiredness;
	float limit_tiredness;
	float thirst;
	float limit_thirst;
	State* actualState;
	std::vector<Node*> grid;
	Vector2D goldNuggetPosition;
	std::string stateNotification;


	Agent();
	~Agent();
	SteeringBehavior *Behavior();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setMass(float mass);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void update(Vector2D steering_force, float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	Path FindPath(const std::vector<Node*>&, const Vector2D&, const Vector2D&);
	float Heuristic(Node*, Node*);
	void Think();
	void ChangeState(nextState);
	void SetGrid(std::vector<Node*> newGrid) { grid = newGrid;}
	Vector2D GetCenteredPosition();
	void SetGoldNuggetPosition(Vector2D newPosition) { goldNuggetPosition = newPosition; }
	Vector2D GetGoldNuggetPosition() { return goldNuggetPosition; }
};

class CompareDist
{
public:
	bool operator()(std::pair<int, Node*> n1, std::pair<int, Node*> n2) {
		return n1.first > n2.first;
	}
};

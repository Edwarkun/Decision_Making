#pragma once
#include "SDL_SimpleApp.h"
#include <vector>
class NodeGOAP {
private:
	Vector2D position;
	float cost;
	std::vector<NodeGOAP*> NB;
public:
	NodeGOAP(const Vector2D& pos, const float& cst) : position(pos), cost(cst) {};
	inline void SetPosition(Vector2D newPos) { position = newPos; }
	inline Vector2D GetPosition() { return position; }
	inline float GetCost() { return cost; }
	inline void SetCost(float newCost) { cost = newCost; }
	inline void AddNB(NodeGOAP* newNB) { NB.push_back(newNB); }
	inline std::vector<NodeGOAP*> GetNB() { return NB; }
	void RemoveNB(NodeGOAP* targetNB) {
		for (int i = 0; i < NB.size(); i++) {
			if (NB[i] == targetNB) {
				NB.erase(NB.begin() + i);
				break;
			}
		}
	}
};
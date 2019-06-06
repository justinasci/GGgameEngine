#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Transfrom.h"
#include "Renderable.h"
#include "RenderSystem.h"
#include "SFML/Graphics.hpp"
#include <stack>
#include <vector>

class Scene : public sf::Drawable
{
public:
	Scene() {
		systems.push_back(new RenderSystem());
	}
	void update(float delta);
	void addGameObject(GameObject* go);
	void removeGameObject(GameObject* go);
	void addSystem(System* sys);
	void removeSystem(System* sys);

private:
	std::vector<GameObject*> gameObjects;
	std::stack<GameObject*> toBeAdded;
	std::stack<GameObject*> toBeRemoved;
	std::vector<GameObject*> dirtyObjects;
	std::vector<System*> systems;
	bool running = false;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		auto  rs = static_cast<RenderSystem*>(systems[0]);
		rs->draw(target, states);
	};
};
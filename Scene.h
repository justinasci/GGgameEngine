#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Transfrom.h"
#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <stack>
#include <vector>

class Scene : public sf::Drawable
{
public:
	Scene() {

	}
	void update(float delta);
	void addGameObject(GameObject* go);
	void removeGameObject(GameObject* go);
	void updateRenderable();
	void addRenderable(GameObject* go);

private:
	std::vector<GameObject*> gameObjects;

	std::stack<GameObject*> toBeAdded;
	std::stack<GameObject*> toBeRemoved;
	std::vector<GameObject*> dirtyObjects;

	std::vector<RenderComponent* > renderComponents;
	bool running = false;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		for (auto rc : renderComponents) {
			rc->draw(target, states, *rc->getTransfrom());
		}

		//for (GameObject* o : gameObjects) {
		//	Sprite* sp = o->getComponent<Sprite>();
		//	if (sp != nullptr) {
		//		Transform* tr = o->getComponent<Transform>();
		//		// target.draw(sp->sprite, tr->transform);
		//	}
		//}
	
	};
};
#pragma once
#include "GameObject.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "Comps.h"
#include <iostream>
#include <stack>

class Scene : public sf::Drawable
{
public:
	Scene() {

	}
	void update(float delta) {
		int lengthGameObjects = gameObjects.size();
		dirtyObjects.clear();
		for (int i = 0; i < lengthGameObjects; i++) {
			gameObjects[i]->update(delta);
			bool dirty = gameObjects[i]->getIsDirty();
			if (dirty) {
				dirtyObjects.push_back(gameObjects[i]);
			}
		}

#ifdef _DEBUG
		std::cout << "Total gameObjects in scene: " << toBeAdded.size() << "\n";
#endif

		while (!toBeAdded.empty()) {
			gameObjects.push_back(toBeAdded.top());
			dirtyObjects.push_back(toBeAdded.top());
			toBeAdded.pop();
		}

		if (dirtyObjects.size() > 0) {
			for (auto dgo : dirtyObjects) {
				//Update Systems
				addRenderable(dgo);
			}
		}
	}

	void addGameObject(GameObject* go) {
		go->setScene(this);
		toBeAdded.push(go);
	}

	void removeGameObject(GameObject* go) {
		go->setIsDisabled(true);
		toBeRemoved.push(go);
	}

	void updateRenderable() {
		renderComponents.clear();
		for (auto go : gameObjects) {
			addRenderable(go);
		}
	}

	void addRenderable(GameObject* go) {
		auto rc = go->getComponent<RenderComponent>();
		renderComponents.push_back(rc);
	}

private:
	std::vector<GameObject*> gameObjects;

	std::stack<GameObject*> toBeAdded;
	std::stack<GameObject*> toBeRemoved;
	std::vector<GameObject*> dirtyObjects;

	std::vector<RenderComponent* > renderComponents;
	bool running = false;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		/*for (auto rc : renderComponents) {
			rc->draw(target, states, rc->getTransfrom()->transform);
		}*/

		//for (GameObject* o : gameObjects) {
		//	Sprite* sp = o->getComponent<Sprite>();
		//	if (sp != nullptr) {
		//		Transform* tr = o->getComponent<Transform>();
		//		// target.draw(sp->sprite, tr->transform);
		//	}
		//}
	
	};
};
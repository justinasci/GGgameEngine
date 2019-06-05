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
		bool isDirty = false;
		for (int i = 0; i < lengthGameObjects; i++) {
			gameObjects[i]->update(delta);
			if (isDirty == false) {
				isDirty = gameObjects[i]->getIsDirty();
			}
		}

		while (!toBeAdded.empty()) {
			gameObjects.push_back(toBeAdded.top());
			addRenderable(toBeAdded.top());
			toBeAdded.pop();
		}

		if (isDirty) {
			updateRenderable();
		} else if (lengthGameObjects < gameObjects.size()) {
			// addRenderable(gameObjects[gameObjects.size() - 1]);
		}
	}

	void addGameObject(GameObject* go) {
		go->setScene(this);
		//gameObjects.push_back(go);
		toBeAdded.push(go);
		std::cout << "Total gameObjects in scene: " << gameObjects.size() << "\n" ;
	}

	void removeGameObject(GameObject* go) {
		std::remove(gameObjects.begin(), gameObjects.end(), go);
		delete go;
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
	std::vector<RenderComponent* > renderComponents;
	bool running = false;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		for (auto rc : renderComponents) {
			rc->draw(target, states, rc->getComponent<Transform>()->transform);
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
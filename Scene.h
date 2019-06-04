#pragma once
#include "GameObject.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "Comps.h"
#include <iostream>
class Scene : public sf::Drawable
{
public:
	Scene() {

	}
	void update(float delta) {
		int lengthGameObjects = gameObjects.size();
		for (int i = 0; i < lengthGameObjects; i++) {
			gameObjects[i]->update(delta);
		}
	}

	void addGameObject(GameObject* go) {
		go->setScene(this);
		gameObjects.push_back(go);
		std::cout << "Total gameObjects in scene: " << gameObjects.size() << "\n" ;
	}

	void removeGameObject(GameObject* go) {
		std::remove(gameObjects.begin(), gameObjects.end(), go);
		delete go;
	}

private:
	std::vector<GameObject* > gameObjects;
	bool running = false;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (GameObject* o : gameObjects) {
			Sprite* sp = o->getComponent<Sprite>();
			if (sp != nullptr) {
				Transform* tr = o->getComponent<Transform>();
				target.draw(sp->sprite, tr->transform);
			}
		}
	
	};
};
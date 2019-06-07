#include "Scene.h"
#include "GameObject.h"
#include "Renderable.h"
#include "System.h"
#include <algorithm>
#include <iostream>

void Scene::update(float delta) {
	size_t lengthGameObjects = gameObjectsGO.size();

	for (size_t i = 0; i < lengthGameObjects; i++) {
		gameObjectsGO[i]->update(delta);
		bool dirty = gameObjectsGO[i]->getIsDirty();
		if (dirty) {
			dirtyObjects.push_back(gameObjectsGO[i]);
		}
	}

#ifdef _DEBUG
	if (toBeAddedGO.size() > 0) std::cout << "Total gameObjects in scene: " << toBeAddedGO.size() << "\n";
#endif

	while (!toBeAddedGO.empty()) {
		gameObjectsGO.push_back(toBeAddedGO.top());
		dirtyObjects.push_back(toBeAddedGO.top());
		toBeAddedGO.pop();
	}

	if (dirtyObjects.size() > 0) {
		//Update Systems
		for (auto dgo : dirtyObjects) {
			for (auto system : systems) {
				system->addGameObject(dgo);
			}
		}
	}

	while (!toBeRemovedGO.empty()) {
		GameObject* tbr = toBeRemovedGO.top();
		for (auto system : systems) {
			system->removeGameObject(tbr);
		}
		tbr->onDestory();
		gameObjectsGO.erase(std::remove(gameObjectsGO.begin(), gameObjectsGO.end(), tbr), gameObjectsGO.end());
		toBeRemovedGO.pop();
		delete tbr;
	}

	while (!toBeRemovedComponents.empty())
	{
		Component* c = toBeRemovedComponents.top();
		toBeRemovedComponents.pop();
		for (auto system : systems) {
			system->removeComponent(c);
		}
		c->onDestroy();
		delete c;
	}

	dirtyObjects.clear();
}

void Scene::addGameObject(GameObject* go) {
	go->setScene(this);
	toBeAddedGO.push(go);
}

void Scene::removeGameObject(GameObject* go) {
	go->setIsDisabled(true);
	toBeRemovedGO.push(go);
}

void Scene::addSystem(System* system)
{
	systems.push_back(system);
}

void Scene::removeSystem(System* system)
{
	
}

void Scene::removeComponent(Component* c)
{
	toBeRemovedComponents.push(c);
}

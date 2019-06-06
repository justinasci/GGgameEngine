#include "Scene.h"
#include "GameObject.h"
#include "Renderable.h"
#include <iostream>

void Scene::update(float delta) {
	size_t lengthGameObjects = gameObjects.size();

	for (size_t i = 0; i < lengthGameObjects; i++) {
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
		//Update Systems
		for (auto dgo : dirtyObjects) {
			addRenderable(dgo);
		}
	}

	dirtyObjects.clear();
}

void Scene::addGameObject(GameObject* go) {
	go->setScene(this);
	toBeAdded.push(go);
}

void Scene::removeGameObject(GameObject* go) {
	go->setIsDisabled(true);
	toBeRemoved.push(go);
}

void Scene::updateRenderable() {
	renderComponents.clear();
	for (auto go : gameObjects) {
		addRenderable(go);
	}
}

void Scene::addRenderable(GameObject* go) {
	auto rc = go->getComponent<RenderComponent>();
	renderComponents.push_back(rc);
}
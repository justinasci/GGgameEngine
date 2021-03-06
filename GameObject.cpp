#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Comps.h"
#include <algorithm>
GameObject::GameObject()
{
	Transform* t = new Transform();
	addComponent(t);
}

GameObject::GameObject(Scene* scene)
{
	setScene(scene);
	GameObject();
}

GameObject::GameObject(Scene* scene, std::string name)
{
	setName(name);
	setScene(scene);
	GameObject();
}

void GameObject::update(float delta) {
	if (isDisabled) return;
	setIsDirty(false);
	for (int i = 0; i < components.size(); i++) {
		components[i]->update(delta);
	}
}

void GameObject::addComponent(Component* component) {
	component->setOwner(this);
	components.push_back(component);
	component->onInit();
	setIsDirty(true);
}

void GameObject::removeComponent(Component* component)
{
	scene->removeComponent(component);
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void GameObject::setScene(Scene* scene)
{
	this->scene = scene;
}

void GameObject::addGameObject(GameObject* ob)
{
	scene->addGameObject(ob);
}

void GameObject::removeGameObject(GameObject* ob)
{
	scene->removeGameObject(ob);
}

void GameObject::setIsDirty(bool value)
{
	isDirty = value;
}

void GameObject::onDestory()
{
	for (int i = 0; i < components.size(); i++) {
		components[i]->onDestroy();
		delete components[i];
	}
	components.clear();
}

Transform* GameObject::getTransform()
{
	return static_cast<Transform*>(components[0]);
}

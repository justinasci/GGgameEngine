#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Comps.h"
GameObject::GameObject()
{
	Transform* t = new Transform();
	addComponent(t);
}

GameObject::GameObject(Scene* scene)
{
	setScene(scene);
}

void GameObject::update(float delta) {
	setIsDirty(false);
	for (auto it = components.begin(); it != components.end(); ++it) {
		Component* c = *it;
		c->update(delta);
	}
}

void GameObject::addComponent(Component* component) {
	component->setOwner(this);
	components.push_back(component);
	component->onInit();
	setIsDirty(true);
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

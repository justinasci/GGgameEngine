#pragma once
#include "GameObject.h"



class Component
{
public:
	virtual void update(float delta) = 0;
	virtual void init() = 0;
	virtual void destroy() = 0;
	void setOwner(GameObject* owner);
	GameObject* getOwner() { return owner; };

	template <class T>
	void addComponent(T* component) {
		owner->addComponent(component);
	}
	template <class T>
	T* getComponent() {
		T* ptr = owner->getComponent<T>();
		return ptr;
	}

	void removeGameObject(GameObject* ob) {
		owner->removeGameObject(ob);
	}

	void addGameObject(GameObject* ob) {
		owner->addGameObject(ob);
	}

protected:
	bool activated = true;
	GameObject* owner = nullptr;
};

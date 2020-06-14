#pragma once
#include "GameObject.h"


class Transform;
class Component
{
public:
	virtual void update(float delta) = 0;
	virtual void onInit() = 0;
	virtual void onDestroy() = 0;
	void setOwner(GameObject* owner);
	GameObject* getOwner() { return owner; };

	template <class T>
	void addComponent(T* component) {
		owner->addComponent(component);
	}
	template <class T>
	T* getComponent() {
		return owner->getComponent<T>();
	}

	template <class T>
	std::vector<T*> getComponents() {
		return owner->getComponents<T>();
	}

	void destoryOwner() {
		removeGameObject(owner);
	}

	void destory() {
		owner->removeComponent(this);
	}

	void removeGameObject(GameObject* ob) {
		owner->removeGameObject(ob);
	}

	void addGameObject(GameObject* ob) {
		owner->addGameObject(ob);
	}

	Transform* getTransformable() {
		return owner->getTransform();
	};

protected:
	bool activated = true;
	GameObject* owner = nullptr;
};

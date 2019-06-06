#pragma once
#include "SFML\Graphics.hpp"

#include <vector>
class Component;
class Scene;
class Transform;
class GameObject
{
public:
	GameObject();
	GameObject(Scene* scene);
	void update(float delta);

	void setScene(Scene* scene);

	void addGameObject(GameObject* ob);
	void removeGameObject(GameObject* ob);

	bool getIsDirty() { return isDirty;  };
	void setIsDirty(bool value);

	void onDestory();

	Transform* getTransform();

	void addComponent(Component* component);
	template<class T>
	T* getComponent() {
		T* d = nullptr;
		for (Component* c : components) {
			d = dynamic_cast<T*>(c);
			if (d != nullptr) {
				return d;
			}
		}
		return nullptr;
	}
private:
	bool isDirty = false;
	std::vector<Component*> components;
	Scene* scene = nullptr;

};

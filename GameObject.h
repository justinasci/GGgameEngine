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
	GameObject(Scene* scene, std::string name);

	void update(float delta);

	void setScene(Scene* scene);

	void addGameObject(GameObject* ob);
	void removeGameObject(GameObject* ob);

	bool getIsDirty() { return isDirty;  };
	void setIsDirty(bool value);

	bool getIsDisabled() { return isDisabled; };
	void setIsDisabled(bool value) { isDisabled = value; }

	std::string getName() { return name; };
	void setName(std::string name) { this->name = name; };

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

	template<class T>
	std::vector<T*> getComponents() {
		std::vector<T*> resultComp;
		T* d = nullptr;
		for (Component* c : components) {
			d = dynamic_cast<T*>(c);
			if (d != nullptr) {
				resultComp.push_back(d);
			}
		}
		return resultComp;
	}

	template<class T>
	void removeComponent() {
		Component* c = getComponent<T>();
		removeComponent(c);
	}

	void removeComponent(Component* component);

private:
	bool isDirty = false;
	bool isDisabled = false;
	std::string name = "";
	std::vector<Component*> components;
	Scene* scene = nullptr;

};

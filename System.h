#pragma once
#include "GameObject.h"
#include "Component.h"
class System
{
public:
	virtual void addGameObject(GameObject *) = 0;
	virtual void removeGameObject(GameObject*) = 0;
	virtual void removeComponent(Component*) = 0;
	virtual void update() = 0;
};


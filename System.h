#pragma once
#include "GameObject.h"
class System
{
public:
	virtual void addGameObject(GameObject *) = 0;
	virtual void removeGameObject(GameObject*) = 0;
	virtual void update() = 0;
};


#pragma once
#include "Component.h"
class Transform : public Component, public sf::Transform
{
public:

	// Inherited via Component
	virtual void update(float delta) override {

	};

	virtual void onInit() override {

	};

	virtual void onDestroy() override {

	};

};
#pragma once
#include "System.h"
#include "Renderable.h"
#include "Transfrom.h"
#include <vector>
class RenderSystem: public System
{
public:
	RenderSystem();
	~RenderSystem();
	// Inherited via System
	virtual void addGameObject(GameObject* go) override;
	virtual void removeGameObject(GameObject*) override;
	virtual void removeComponent(Component* c) override;
	virtual void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (auto c : renderComponents) {
			c->draw(target, states, c->getTransformable()->getTransform());
		}
	}

private:
	std::vector<RenderComponent*> renderComponents;
};


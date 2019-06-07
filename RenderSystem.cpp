#include "RenderSystem.h"
#include <algorithm>
RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::addGameObject(GameObject* go)
{
	auto list = go->getComponents<RenderComponent>();
	for (auto rc : list) {
		renderComponents.push_back(rc);
	}
}

void RenderSystem::removeGameObject(GameObject* go)
{
	auto list = go->getComponents<RenderComponent>();
	for (auto rc : list) {
		removeComponent(rc);
	}
}

void RenderSystem::removeComponent(Component* c)
{
	renderComponents.erase(std::remove(renderComponents.begin(), renderComponents.end(), c), renderComponents.end());
}

void RenderSystem::update()
{

}

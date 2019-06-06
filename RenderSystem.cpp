#include "RenderSystem.h"

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

void RenderSystem::removeGameObject(GameObject*)
{

}

void RenderSystem::update()
{

}

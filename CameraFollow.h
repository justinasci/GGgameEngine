#pragma once
#include "Component.h"
#include "Transfrom.h"
#include "Events.h"
class CameraFollow :
	public Component {
public:
	CameraFollow(sf::RenderWindow* window) {
		this->window = window; 
		t = nullptr;
	}
	virtual void update(float delta) override {
		auto view = window->getDefaultView();
		view.setCenter(t->getPosition());
		auto scroll = Events::getMouseWheelEvent();
		if (scroll.delta != 0) {
			zoomLevel += 0.1 * scroll.delta;
		}
		view.zoom(zoomLevel);
		window->setView(view);
		std::cout << t->getPosition().x << std::endl;
	};
	virtual void onInit() override {
		t = getTransformable();
	};
	virtual void onDestroy() override {};
	sf::RenderWindow* window;
	Transform* t;
	float zoomLevel = 1.0f;
};

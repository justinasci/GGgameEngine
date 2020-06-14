#pragma once
#include "Component.h"
#include "Transfrom.h"

class CameraFollow :
	public Component {
public:
	CameraFollow(sf::RenderWindow* window) {
		this->window = window;
	}
	virtual void update(float delta) override {
		std::cout << t->getPosition().x << " " << t->getPosition().y << std::endl;
		auto view = window->getDefaultView();
		view.setCenter(t->getPosition());
		window->setView(view);
	};
	virtual void onInit() override {
		t = getTransformable();
	};
	virtual void onDestroy() override {};
	sf::RenderWindow* window;
	Transform* t;

};

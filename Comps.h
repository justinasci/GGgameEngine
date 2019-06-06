#pragma once
#include "Component.h"
#include "Renderable.h"
#include "SFML/Graphics.hpp"
#include <iostream>


class Transform: public Component
{
public:

	sf::Transform transform;
	// Inherited via Component
	virtual void update(float delta) override {

	};

	virtual void onInit() override {

	};

	virtual void onDestroy() override {

	};

};

class Sprite: public RenderComponent
{
public:
	// Inherited via Component
	sf::Sprite sprite;
	virtual void update(float delta) override {
		//std::cout << "Sprite: " << family() << "\n";
	};
	virtual void onInit() override {};
	virtual void onDestroy() override {};
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states, sf::Transform t) const {
		target.draw(sprite, t);
	}
};

class Spinner : public Component {
public:

	Transform* t = nullptr;
	void update(float delta) {
		t->transform.rotate(90 * delta);
	}

	void onInit() {
		t = getTransfrom();
	}

	void onDestroy() {};
};

class RemovAfterTime : public Component {
	// Inherited via Component
	float timer = 0.0f;
	virtual void update(float delta) override {
		timer += delta;

		if (timer > 5.0f) {
			this->destoryOwner();
		}
	};
	virtual void onInit() override {};
	virtual void onDestroy() override {};
};

class PlayerController : public Component
{
public:
	Transform* t;
	float speed = 100.0f;



	void update(float delta)
	{
		sf::Vector2f dpos = sf::Vector2f();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dpos.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dpos.x += speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dpos.y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dpos.y += speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			for (int i = 0; i < 1; i++) {
				Sprite* sp = getComponent<Sprite>();
				GameObject* b = makeBullet(sp->sprite, t->transform);
				addGameObject(b);
			}
		}

		//std::cout << "Player: " << family() << "\n";

		t->transform.translate(dpos* delta);
	}

	void onInit()
	{
		t = getTransfrom();
	}

	void onDestroy()
	{
		
	}

private: 
	GameObject* makeBullet(sf::Sprite s, sf::Transform t) {
		GameObject* bullet = new GameObject();
		Transform* tr = bullet->getComponent<Transform>();
		tr->transform = t;
		Sprite* sp = new Sprite();
		sp->sprite = s;
		bullet->addComponent(sp);
		bullet->addComponent(new Spinner());
		return bullet;
	}
};


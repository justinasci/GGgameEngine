#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"



class Transform: public Component
{
public:

	sf::Transform transform;
	// Inherited via Component
	virtual void update(float delta) override {

	};

	virtual void init() override {

	};

	virtual void destroy() override {

	};

};

class Sprite: public Component
{
public:
	// Inherited via Component
	sf::Sprite sprite;
	virtual void update(float delta) override {};
	virtual void init() override {};
	virtual void destroy() override {};
};

class Spinner : public Component {
public:

	Transform* t;
	void update(float delta) {
		t->transform.rotate(90 * delta);
	}

	void init() {
		t = getComponent<Transform>();
	}

	void destroy() {};
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
			Sprite* sp = getComponent<Sprite>();
			GameObject* b = makeBullet(sp->sprite, t->transform);
			addGameObject(b);
			
		}

		t->transform.translate(dpos* delta);
	}

	void init()
	{
		t = getComponent<Transform>();
	}

	void destroy()
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


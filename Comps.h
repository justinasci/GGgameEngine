#pragma once
#include "Component.h"
#include "Renderable.h"
#include "Transfrom.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include <iostream>

class Sprite: public RenderComponent, public sf::Sprite
{
public:
	// Inherited via Component
	virtual void update(float delta) override {
		//std::cout << "Sprite: " << family() << "\n";
	};
	virtual void onInit() override {};
	virtual void onDestroy() override {};
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states, sf::Transform t) const {
		target.draw(*this, t);
	}

	Sprite& operator= (const sf::Sprite& other) {
		this->setTexture(*other.getTexture());
		this->setTextureRect(other.getTextureRect());
		return *this;
	}

};

class AnimatedSprite : public Sprite
{
public:
	virtual void update(float delta) override {
		timer += delta;
		if (timer > frameSwitch) {
			frame_counter++;
			timer = 0.0f;
		}
	};
	virtual void onInit() override {};
	virtual void onDestroy() override {};
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform t) const {
		auto arr = bundle.at(frameID);
		sf::Sprite sp = arr[frame_counter % arr.size()];
		target.draw(sp, t );
	}

	void setBundle(SpriteBundle b) {
		bundle = b;
	}

	SpriteBundle getBundle() {
		return bundle;
	}

	void setFrameId(RSBID id) {
		if (frameID != id) {
			frameID = id;
			frame_counter = 0;
		}
	}

	RSBID getFrameId() {
		return frameID;
	}

	void setFrameTime(float t) {
		frameSwitch = t;
		frame_counter = 0;
	}

private:
	SpriteBundle bundle;
	RSBID frameID;
	float timer = 0.0f;
	float frameSwitch = 0.08f;
	int frame_counter = 0;
};


class Spinner : public Component {
public:

	Transform* t = nullptr;
	void update(float delta) {
		t->rotate(90 * delta);
	}

	void onInit() {
		t = getTransformable();
	}

	void onDestroy() {};
};

class RemovAfterTime : public Component {
	// Inherited via Component
	float timer = 0.0f;
	virtual void update(float delta) override {
		timer += delta;

		if (timer > 1.0f) {
			this->destory();
		}
	};
	virtual void onInit() override {};
	virtual void onDestroy() override {};
};

class PlayerController : public Component
{
public:
	Transform* t = nullptr;
	AnimatedSprite* sp = nullptr;
	float speed = 100.0f;
	bool isLookingLeft = true;

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
				GameObject* b = makeBullet(sp, *t);
				addGameObject(b);
			}
		}

		if (dpos.x != 0.0f || dpos.y != 0.0f) {
			sp->setFrameId("run");
			if (dpos.x < 0.f && !isLookingLeft) {
				isLookingLeft = true;
				t->scale(sf::Vector2f(-1, 1));
			}
			else if (dpos.x > 0.f && isLookingLeft) {
				isLookingLeft = false;
				t->scale(sf::Vector2f(-1, 1));
			}
			t->move(dpos * delta);
		}
		else {
			sp->setFrameId("idle");
		}

	}

	void onInit()
	{
		t = getTransformable();
		t->move(200, 200);
		sp = getComponent<AnimatedSprite>();
	}

	void onDestroy()
	{
		
	}

private: 
	GameObject* makeBullet(Sprite* s, Transform t) {
		GameObject* bullet = new GameObject();
		Transform* tr = bullet->getTransform();
		RemovAfterTime* rm = new RemovAfterTime();
		Sprite* sp = new Sprite();
		*sp = *s;
		*tr = t;
		bullet->addComponent(sp);
		bullet->addComponent(rm);
		bullet->addComponent(new Spinner());
		return bullet;
	}
};


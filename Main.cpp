#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Comps.h"
#include "Resources.h"
#include "World.h"
#include "CameraFollow.h"
#include "Utils.h"

void buildWorld(Scene& scene) {
	GameObject* gob = new GameObject();
	World* worldComponent = new World();
	gob->addComponent(worldComponent);
	scene.addGameObject(gob);
}


void buildScene(Scene& scene, sf::RenderWindow& window) {

	GameObject* gob = new GameObject();
	AnimatedSprite* sprite = new AnimatedSprite();
	sprite->setBundle(*RSB::get("banditas"));
	sprite->setFrameId("idle");
	gob->addComponent(sprite);
	PlayerController* pc = new PlayerController();
	gob->addComponent(pc);
	sf::View view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));
	window.setView(view);
	CameraFollow* cam = new CameraFollow(&window);
	gob->addComponent(cam);
	scene.addGameObject(gob);
}


std::vector<sf::Sprite> subvector(std::vector<sf::Sprite> vec, int s, int e) {
	std::vector<sf::Sprite>::const_iterator first = vec.begin() + s;
	std::vector<sf::Sprite>::const_iterator last = vec.begin() + e;
	return std::vector<sf::Sprite>(first, last);
}

int main()
{
	RTX::load("banditas", "resources//banditas.png");
	RTX::load("grass", "resources//grass_tileset_16x16.png");
	RTX::load("test", "resources//test.png");
	 
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	auto sp = loadSpriteSheet(RTX::get("banditas"), 8, 7, 0, 5);
	SpriteBundle sb;
	sb["idle"] = subvector(sp[0], 0, 4);
	sb["run"] = sp[1];
	sb["attack"] = sp[2];
	sb["die"] = sp[3];
	RSB::add("banditas", &sb);

	auto grass = loadSpriteSheet(RTX::get("grass"), 16, 16);

	int i = 0;

	Scene scene;
	buildScene(scene, window);
	buildWorld(scene);
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Time dt = deltaClock.restart();
#ifdef _DEBUG
		std::cout << 1.f / ((float)dt.asMicroseconds() / 1000000.f) << " fps \n";
#endif
		scene.update((float)dt.asMicroseconds() / 1000000.f);
		window.clear();
		window.draw(scene);
		window.display();

	}
	return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Comps.h"
#include "Resources.h"

sf::Texture* loadTexture(const std::string fileName) {
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(fileName)) {
		throw "NEVEIKIA";
	}
	return texture;
}

std::vector<std::vector<sf::Sprite>> loadSpriteSheet(sf::Texture* texture, int widthTiles, int heightTiles, int fromRow = 0, int toRow = -1, int fromCol = 0, int toCol = -1) {
	std::vector<std::vector<sf::Sprite> > bundle;
	sf::Vector2u imgSize = texture->getSize();
	sf::Vector2u tileSize = sf::Vector2u(imgSize.x / widthTiles, imgSize.y / heightTiles);
	int endRow = toRow == -1 ? widthTiles : toRow;
	int endCol = toCol == -1 ? heightTiles : toCol;

	for (int h = fromRow; h <= endRow; h++) {
		std::vector<sf::Sprite> frames;
		for (int w = fromCol; w <= endCol; w++) {
			sf::Sprite s = sf::Sprite(*texture, sf::IntRect(w * tileSize.x, h * tileSize.y, tileSize.x, tileSize.y));
			s.move(-(float)tileSize.x / 2.0f, -(float)tileSize.y / 2.0f);
			frames.push_back(s);
		}
		bundle.push_back(frames);
	}
	return bundle;
}

void buildScene(Scene& scene) {
	GameObject* gob = new GameObject();
	AnimatedSprite* sprite = new AnimatedSprite();
	sprite->setBundle(*RSB::get("banditas"));
	sprite->setFrameId("idle");
	gob->addComponent(sprite);
	PlayerController* pc = new PlayerController();
	gob->addComponent(pc);
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
	buildScene(scene);
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
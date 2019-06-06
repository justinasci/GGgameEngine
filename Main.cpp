#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

#include "Comps.h"

struct SpriteSheet {
	sf::Texture* texture;
	std::vector<sf::Sprite> frames;
};

sf::Texture* loadTexture(const std::string fileName) {
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(fileName)) {
		throw "NEVEIKIA";
	}
	return texture;
}

SpriteSheet loadSpriteSheet(sf::Texture* texture, int widthTiles, int heightTiles, int fromRow = 0, int toRow = -1, int fromCol = 0, int toCol = -1) {
	std::vector<sf::Sprite> frames;
	sf::Vector2u imgSize = texture->getSize();
	sf::Vector2u tileSize = sf::Vector2u(imgSize.x / widthTiles, imgSize.y / heightTiles);

	int endRow = toRow == -1 ? widthTiles : toRow;
	int endCol = toCol == -1 ? heightTiles : toCol;

	for (int h = fromRow; h < endRow; h++) {
		for (int w = fromCol; w < endCol; w++) {
			frames.push_back(sf::Sprite(*texture, sf::IntRect( w * tileSize.x, h * tileSize.y, tileSize.x, tileSize.y)));
		}
	}
	return {texture, frames };
}

void buildScene(Scene& scene, SpriteSheet sp) {
	GameObject* gob = new GameObject();
	Sprite* sprite = new Sprite();
	sprite->sprite = sp.frames[0];
	gob->addComponent(sprite);
	PlayerController* pc = new PlayerController();
	gob->addComponent(pc);
	scene.addGameObject(gob);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	auto sp = loadSpriteSheet(loadTexture("resources//banditas.png"), 8, 7, 0, 6);
	auto grass = loadSpriteSheet(loadTexture("resources//grass_tileset_16x16.png"), 16, 16);

	int i = 0;

	Scene scene;
	buildScene(scene, sp);
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
		scene.update((float)dt.asMicroseconds()/1000000.f);
		window.clear();
		window.draw(scene);
		window.display();

	}
	return 0;
}
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

static sf::Texture* loadTexture(const std::string fileName) {
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(fileName)) {
		throw "NEVEIKIA";
	}
	return texture;
}

static std::vector<std::vector<sf::Sprite>> loadSpriteSheet(sf::Texture* texture, int widthTiles, int heightTiles, int fromRow = 0, int toRow = -1, int fromCol = 0, int toCol = -1) {
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

static std::vector<sf::Sprite> subvector(std::vector<sf::Sprite> vec, int s, int e) {
	std::vector<sf::Sprite>::const_iterator first = vec.begin() + s;
	std::vector<sf::Sprite>::const_iterator last = vec.begin() + e;
	return std::vector<sf::Sprite>(first, last);
}
#pragma once
#include "Component.h"
#include "SFML\Graphics.hpp"
class RenderComponent: public Component {
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform t) const = 0;
};
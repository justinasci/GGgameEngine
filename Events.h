#pragma once
#include <SFML/Graphics.hpp>
class Events {
public: 
	static void setMouseWheelEvent(sf::Event::MouseWheelScrollEvent eventas);
	static sf::Event::MouseWheelScrollEvent getMouseWheelEvent();
	static sf::Event::MouseWheelScrollEvent mouseWheelScrollEvent;
};
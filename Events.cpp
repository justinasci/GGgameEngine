#include "Events.h"

sf::Event::MouseWheelScrollEvent Events::mouseWheelScrollEvent = {};

void Events::setMouseWheelEvent(sf::Event::MouseWheelScrollEvent eventas)
{
	Events::mouseWheelScrollEvent = eventas;
}

sf::Event::MouseWheelScrollEvent Events::getMouseWheelEvent()
{
	return Events::mouseWheelScrollEvent;
}

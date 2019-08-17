#include "tool_type_strategy.h"

#include <cmath>
#include <iostream>

#include "../canvas.h"

void LineToolStrategy::handleMouseDown(sf::Event e, [[maybe_unused]] Canvas& canvas, [[maybe_unused]] const Options& options) {
    m_mouseDownLocation = {(float)e.mouseButton.x, (float)e.mouseButton.y};
	std::cout << m_mouseDownLocation.x << " " << m_mouseDownLocation.y << std::endl;
}

void LineToolStrategy::handleMouseUp([[maybe_unused]] sf::Event e, Canvas& canvas, [[maybe_unused]] const Options& options) {
	float dx = m_mouseDownLocation.x - m_mouseCurrentLocation.x;
	float dy = m_mouseDownLocation.y - m_mouseCurrentLocation.y;

	float length = std::sqrt(dx * dx + dy + dy);

	float normX = dx / length;
	float normY = dy / length;

	sf::Vector2f cursorPos = m_mouseDownLocation;
	for (float i = 0; i < length; i++) {
		canvas.changePixel(
			(unsigned)cursorPos.x,
			(unsigned)cursorPos.y,
			sf::Color::Black);
		cursorPos -= {normX, normY};
	}
}

void LineToolStrategy::handleMouseMove(sf::Event e, [[maybe_unused]] Canvas& canvas, [[maybe_unused]] const Options& options) {
    m_mouseCurrentLocation = {(float)e.mouseMove.x, (float)e.mouseMove.y};
}

void LineToolStrategy::renderPreview(sf::RenderWindow& window) {
    std::vector<sf::Vertex> line = {
        sf::Vertex(m_mouseDownLocation, sf::Color::Black),
        sf::Vertex(m_mouseCurrentLocation, sf::Color::Black),
    };

    window.draw(line.data(), 2, sf::Lines);
}

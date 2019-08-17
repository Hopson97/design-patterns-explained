#include "tool_type_strategy.h"

#include "../canvas.h"

void SquareToolStrategy::handleMouseDown(sf::Event e, [[maybe_unused]] Canvas& canvas, [[maybe_unused]] const Options& options) {
    m_mouseCurrentLocation = {(float)e.mouseMove.x, (float)e.mouseMove.y};
}

void SquareToolStrategy::handleMouseUp([[maybe_unused]]  sf::Event e, Canvas& canvas, [[maybe_unused]] const Options& options) {
    	for (float x = m_mouseDownLocation.x; x < m_mouseCurrentLocation.x; x++) {
		canvas.changePixel(
			(unsigned)x,
			(unsigned)m_mouseDownLocation.y,
			sf::Color::Black
		);
		canvas.changePixel(
			(unsigned)x,
			(unsigned)m_mouseCurrentLocation.y,
			sf::Color::Black
		);
	}
	for (float y = m_mouseDownLocation.y; y < m_mouseCurrentLocation.y; y++) {
		canvas.changePixel(
			(unsigned)m_mouseDownLocation.x,
			(unsigned)y,
			sf::Color::Black
		);
		canvas.changePixel(
			(unsigned)m_mouseCurrentLocation.x,
			(unsigned)y,
			sf::Color::Black
		);
	}
}

void SquareToolStrategy::handleMouseMove(sf::Event e, [[maybe_unused]] Canvas& canvas, [[maybe_unused]] const Options& options) {
    m_mouseCurrentLocation = {(float)e.mouseMove.x, (float)e.mouseMove.y};
}

void SquareToolStrategy::renderPreview(sf::RenderWindow& window) {
    sf::RectangleShape square;
    square.setOutlineColor(sf::Color::Black);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(1);
    square.setPosition(m_mouseDownLocation);
    square.setSize({
        m_mouseCurrentLocation.x - m_mouseDownLocation.x,
        m_mouseCurrentLocation.y - m_mouseDownLocation.y
    });
    window.draw(square);
}

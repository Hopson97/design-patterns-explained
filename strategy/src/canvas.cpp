#include "canvas.h"

#include "constants.h"

#include <iostream>

Canvas::Canvas(unsigned width, unsigned height, unsigned x, unsigned y)
:   m_renderCanvas({WIDTH, HEIGHT})
,   m_bounds(x, y, width, height)
{
    m_canvas.create(width, height, sf::Color::White);
    m_canvasTexture.loadFromImage(m_canvas);
    m_renderCanvas.setTexture(&m_canvasTexture);
    m_renderCanvas.setPosition(x, y);
    m_renderCanvas.setOutlineThickness(3);
    m_renderCanvas.setOutlineColor(sf::Color::Black);
}

void Canvas::update() {
    m_canvasTexture.loadFromImage(m_canvas);
}

void Canvas::render(sf::RenderWindow& window) {
    window.draw(m_renderCanvas);
}

void Canvas::changePixel(unsigned x, unsigned y, sf::Color color) {
    if (isLocationInBounds(x, y)) {
        m_canvas.setPixel(x, y, color);
    }
}    

void Canvas::erasePixel(unsigned x, unsigned y) {
    changePixel(x, y, sf::Color::White);
}

std::optional<sf::Color> Canvas::getPixelColour(unsigned x, unsigned y) const {
    if (isLocationInBounds(x, y)) {
        return m_canvas.getPixel(x, y);
    }
    
    return {};
}

bool Canvas::isLocationInBounds(unsigned x, unsigned y) const {
    return m_bounds.contains(x, y);
}
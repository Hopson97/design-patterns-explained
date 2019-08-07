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
    if (m_bounds.contains(x, y)) {
        m_canvas.setPixel(x - m_bounds.left, y + m_bounds.top, color);
    }
}    

void Canvas::erasePixel(unsigned x, unsigned y) {
    changePixel(x, y, sf::Color::White);
}

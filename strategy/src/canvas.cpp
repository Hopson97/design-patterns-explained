#include "canvas.h"

#include "constants.h"

#include <iostream>

Canvas::Canvas(unsigned width, unsigned height)
:   m_renderCanvas({WIDTH, HEIGHT})
,   m_width (width)
,   m_height(height)
{
    m_canvas.create(m_width, m_height, sf::Color::White);
    m_canvasTexture.loadFromImage(m_canvas);
    m_renderCanvas.setTexture(&m_canvasTexture);
}

void Canvas::update() {
    m_canvasTexture.loadFromImage(m_canvas);
}

void Canvas::render(sf::RenderWindow& window) {
    window.draw(m_renderCanvas);
}

void Canvas::changePixel(unsigned x, unsigned y, sf::Color color) {
    std::cout << x << " " << y << std::endl;
    if (x < m_width && y < m_height) {
        m_canvas.setPixel(x, y, color);
    }
}    

void Canvas::erasePixel(unsigned x, unsigned y) {
    changePixel(x, y, sf::Color::White);
}

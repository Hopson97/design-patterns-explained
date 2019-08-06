#include "canvas.h"

#include "constants.h"

Canvas::Canvas()
:   m_renderCanvas({WIDTH, HEIGHT}) {
    m_canvas.create(WIDTH, HEIGHT, sf::Color::White);
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
    if (x >= WIDTH || y >= HEIGHT) {
        return;
    }

    m_canvas.setPixel(x, y, color);
}    
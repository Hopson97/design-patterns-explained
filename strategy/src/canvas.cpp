#include "canvas.h"

#include "constants.h"

Canvas::Canvas()
:   m_renderCanvas({WIDTH, HEIGHT}) {
    m_canvas.create(WIDTH, HEIGHT);
    m_canvasTexture.loadFromImage(m_canvas);
    m_renderCanvas.setTexture(&m_canvasTexture);
}

void Canvas::update() {
    m_canvasTexture.loadFromImage(m_canvas);
}

void Canvas::render(sf::RenderWindow& window) {
    window.draw(m_renderCanvas);
}
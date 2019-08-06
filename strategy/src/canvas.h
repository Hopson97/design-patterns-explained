#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Canvas {
    public:
        Canvas();

        void update();
        void render(sf::RenderWindow& window);

    private:
        sf::Image m_canvas;
        sf::Texture m_canvasTexture;
        sf::RectangleShape m_renderCanvas;
};
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

/**
 * @brief The class that holds information about the image
 * the user is drawing onto
 * 
 */
class Canvas {
    public:
        /**
         * @brief Construct a new Canvas object
         * Initilizes data required for canvas to operate
         */
        Canvas();

        /**
         * @brief Update the canvas image to display what has been drawn since last update
         * 
         */
        void update();

        /**
         * @brief Render the canvas image onto the window
         * 
         * @param window The window 
         */
        void render(sf::RenderWindow& window);

        void changePixel(unsigned x, unsigned y, sf::Color color);        

    private:
        sf::Image m_canvas;
        sf::Texture m_canvasTexture;
        sf::RectangleShape m_renderCanvas;
};
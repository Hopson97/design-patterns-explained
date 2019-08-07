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
         * @param width The width of the canvas in pixels 
         * @param height The height of the canvas in pixels
         */
        Canvas(unsigned width, unsigned height, unsigned x, unsigned y);

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

        /**
         * @brief Change the colour of a pixel
         * 
         * @param x The x-coordinate to change
         * @param y The y-coordinate to change
         * @param color The colour to change the pixel colour to
         */
        void changePixel(unsigned x, unsigned y, sf::Color color); 

        /**
         * @brief Erases a pixel from the canvas
         * 
         * @param x The x-coordinate to erase
         * @param y The y-coordinate to erase
         */
        void erasePixel(unsigned x, unsigned y);       

    private:
        sf::Image m_canvas;
        sf::Texture m_canvasTexture;
        sf::RectangleShape m_renderCanvas;

        const sf::IntRect m_bounds;
};